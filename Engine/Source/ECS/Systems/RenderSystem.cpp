#include "Pch.h"
#include "RenderSystem.h"
#include "Rendering/Renderer/Renderer.h"
#include "ECS/ECS.h"
#include "ECS/Components/CoreComponents.h"


#include "Platform/Window/Window.h"
#include <Rendering/Texture/Subtexture2D.h>
#include "Resources/ResourceHolder.h"

namespace Hi_Engine
{
	RenderSystem::RenderSystem(ECSCoordinator& ecs, Renderer& renderer, std::weak_ptr<Editor> editor, const IVector2& size)
	: System{ ecs }, m_renderer{ renderer }, m_editor{ editor }, m_windowSize{ size }
	{
	}

	void RenderSystem::HandleEvent(WindowEvent& event)
	{
		if (event.GetEventType() == eWindowEvent::Resize)
		{
			m_windowSize = event.GetSize();
		}
	}

	void RenderSystem::Update(float deltaTime)
	{
		m_renderer.ClearScreen(); // or have part of the process function call?

		const auto& cameraComponents = m_ecs.GetComponents<CameraComponent>();
		auto cameraIterator = std::find_if(cameraComponents.begin(), cameraComponents.end(), [](const CameraComponent& component) { return component.IsActive; });

		if (cameraIterator == cameraComponents.end())
			return;


		m_renderer.SetProjectionMatrix(cameraIterator->Camera.GetProjectionMatrix());

		RenderUI();

		m_renderer.SetProjectionMatrix(cameraIterator->Camera.GetViewProjectionMatrix()); // do in function?? Check if any entities to draw before?!
		RenderSprites();


		m_renderer.ProcessCommands(); // mabe not? maybe render direly in RenderUI and RenderSprites???
		//m_window.SwapBuffers();
	}

	eUpdatePhase RenderSystem::GetUpdatePhase() const
	{
		return eUpdatePhase::PostUpdate;
	}

	void RenderSystem::RenderUI()
	{
		static auto sort = [this](Entity lhs, Entity rhs)
		{
			auto* lhsUI = m_ecs.GetComponent<UIComponent>(lhs);
			auto* rhsUI = m_ecs.GetComponent<UIComponent>(rhs);

			return lhsUI->RenderDepth > rhsUI->RenderDepth;
		};
		/*static auto sort = [this](const UIComponent* lhs, const UIComponent* rhs)
		{
			return lhs->RenderDepth > rhs->RenderDepth;
		};*/

		auto componentView = m_ecs.GetComponentView<UIComponent, TransformComponent>(sort);


		Hi_Engine::SpriteBatch spriteBatch;
		spriteBatch.Sprites.reserve(componentView.size());


		for (const auto& [uiComponent, transformComponent] : componentView)
		{
			const auto& [subtexture, defaultColor, currentColor, depth, isVisible] = *uiComponent;

			if (!isVisible)
				continue;

			const auto& [position, scale, pivot, rotation] = *transformComponent;

			const auto& [r, g, b, a] = currentColor;

			float xPosition = position.x * m_windowSize.x;
			xPosition += (scale.x * pivot.x);

			float yPosition = position.y * m_windowSize.y;
			yPosition += (scale.y * pivot.y);

			// todo; valid check subtexture...
			spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { xPosition, yPosition, 0.f }, { scale.x, scale.y }, rotation }, glm::vec4{ r, g, b, a }, subtexture.get());
		}

		//spriteBatch.ProjectionMatrix = proj;
		//Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);

		m_renderer.AddSpriteBatch(std::move(spriteBatch));

	}

	void RenderSystem::RenderSprites()
	{
		// make sure sprites stores render order?

		static auto sort = [this](Entity lhs, Entity rhs)
		{
			const auto* lhsTransform = m_ecs.GetComponent<TransformComponent>(lhs);
			const auto* rhsTransform = m_ecs.GetComponent<TransformComponent>(rhs);

			if (!lhsTransform || !rhsTransform)
				return false;

			return lhsTransform->Position.y < rhsTransform->Position.y;
		};

		auto componentView = m_ecs.GetComponentView<SpriteComponent, TransformComponent>(sort);

		Hi_Engine::SpriteBatch spriteBatch;
		spriteBatch.Sprites.reserve(componentView.size());

		for (const auto& [spriteComponent, transformComponent] : componentView)
		{
			if (!spriteComponent->IsVisible)
				continue;

			glm::vec4 spriteColor = { spriteComponent->CurrentColor.x, spriteComponent->CurrentColor.y, spriteComponent->CurrentColor.z, spriteComponent->CurrentColor.w };

			glm::vec3 position;
			position.x = transformComponent->Position.x + (transformComponent->Pivot.x * transformComponent->Scale.x);
			position.y = transformComponent->Position.y + (transformComponent->Pivot.y * transformComponent->Scale.y);

			spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { position.x, position.y, 0.f }, { transformComponent->Scale.x, transformComponent->Scale.y }, transformComponent->Rotation }, spriteColor, spriteComponent->Subtexture.get());
		}

		m_renderer.AddSpriteBatch(std::move(spriteBatch));
		//spriteBatch.ProjectionMatrix = proj;
		//Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);

	}
}
