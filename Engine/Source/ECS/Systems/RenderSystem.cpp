#include "Pch.h"
#include "RenderSystem.h"
#include "Rendering/Renderer/Renderer.h"
#include "World/World.h"
#include "ECS/Components/CoreComponents.h"


#include "Platform/Window/Window.h"
#include <Rendering/Texture/Subtexture2D.h>
#include "Resources/ResourceHolder.h"

namespace Hi_Engine
{
	RenderSystem::RenderSystem(World& ecs, std::weak_ptr<Renderer> renderer, std::weak_ptr<Editor> editor, const IVector2& size)
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
		// TODO; only sort visible entities!

		PROFILE_FUNCTION("RenderSystem::Update [Begin]");

		if (auto renderer = m_renderer.lock())
		{
			renderer->BeginFrame();
			renderer->ClearScreen(); // or have part of the process function call?

			auto view = m_ecs.GetComponentView<CameraComponent>(); // TODO; use FindIf fnc later...
			Hi_Engine::Camera* camera = nullptr;

			// Find first instead?
			//view.ForEach([&](CameraComponent& component)
			view.ForEach([&](CameraComponent& component)
			{
				if (component.IsActive)
				{
					camera = &component.Camera;
					return false;
				}

				return true;
			});

			if (!camera)
			{
				Logger::LogError("RenderSystem::Update - Failed to find an active Camera!");
				return;
			}

			// Render sprites
			renderer->SetProjectionMatrix(camera->GetViewProjectionMatrix()); // do in function?? Check if any entities to draw before?!
			renderer->AddSpriteBatch(std::move(CreateSpriteBatch()));
			{
				PROFILE_FUNCTION("RenderSystem Process batch 1");
				renderer->ProcessBatches();
			}
		
			// Render UI (with Orthographic Projection)
			renderer->SetProjectionMatrix(camera->GetProjectionMatrix());
			renderer->AddSpriteBatch(std::move(CreateUIBatch())); // TODO; check if batch is empty before?
			renderer->ProcessBatches();
			
			renderer->EndFrame(); //m_window.SwapBuffers();
		}
	}

	eUpdatePhase RenderSystem::GetUpdatePhase() const
	{
		return eUpdatePhase::PostUpdate;
	}

	SpriteBatch RenderSystem::CreateSpriteBatch() const
	{
		PROFILE_FUNCTION("\tRenderSystem::CreateSpriteBatch");

		const auto componentView = m_ecs.GetComponentView<SpriteComponent, TransformComponent>();

		SpriteBatch spriteBatch;
		spriteBatch.Sprites.reserve(componentView.size());

		//componentView.ForEach([&](const SpriteComponent* spriteComponent, const TransformComponent* transformComponent) 
		componentView.ForEach([&](const SpriteComponent& spriteComponent, const TransformComponent& transformComponent) 
			{
				if (!spriteComponent.IsVisible || !spriteComponent.Subtexture)
					return;

				const FVector2& scale = transformComponent.Scale;
				const float& rotation = transformComponent.Rotation;

				float xPosition = transformComponent.Position.x + (transformComponent.Pivot.x * scale.x);
				float yPosition = transformComponent.Position.y + (transformComponent.Pivot.y * scale.y);

				const auto& [r, g, b, a] = spriteComponent.CurrentColor;

				spriteBatch.Sprites.emplace_back(Transform{ { xPosition, yPosition, 0.f }, { scale.x, scale.y }, transformComponent.Rotation }, glm::vec4{ r, g, b, a }, spriteComponent.Subtexture.get());
			});

		auto& sprites = spriteBatch.Sprites;
		std::sort(sprites.begin(), sprites.end(), [](const Sprite& lhs, const Sprite& rhs) { return lhs.Transform.Position.y < rhs.Transform.Position.y; });

		return spriteBatch;
	}

	SpriteBatch RenderSystem::CreateUIBatch() const
	{
		PROFILE_FUNCTION("\tRenderSystem::CreateUIBatch");

		auto componentView = m_ecs.GetComponentView<UIComponent, TransformComponent>();
		
		/*auto componentView = m_ecs.GetComponentView<UIComponent, TransformComponent>([this](Entity lhs, Entity rhs)
		{
			const auto* lhsUI = m_ecs.GetComponent<UIComponent>(lhs);
			const auto* rhsUI = m_ecs.GetComponent<UIComponent>(rhs);
			
			return lhsUI->RenderDepth > rhsUI->RenderDepth;
		});*/

		SpriteBatch spriteBatch;
		spriteBatch.Sprites.reserve(componentView.size());

		componentView.ForEach([&](const UIComponent& uiComponent, const TransformComponent& transformComponent)
		{
				if (!uiComponent.IsVisible || !uiComponent.Subtexture)
					return;

				const FVector2& scale = transformComponent.Scale;
				const float& rotation = transformComponent.Rotation;

				float xPosition = transformComponent.Position.x * m_windowSize.x;
				xPosition += (scale.x * transformComponent.Pivot.x);

				float yPosition = transformComponent.Position.y * m_windowSize.y;
				yPosition += (scale.y * transformComponent.Pivot.y);

				const auto& [r, g, b, a] = uiComponent.CurrentColor;

				spriteBatch.Sprites.emplace_back(Transform{ { xPosition, yPosition, 0.f }, { scale.x, scale.y }, rotation }, glm::vec4{ r, g, b, a }, uiComponent.Subtexture.get());

		});

		// Will this work when it should be render depth?? -> maybe solution is to use render depth for z or something
		auto& sprites = spriteBatch.Sprites;
		std::sort(sprites.begin(), sprites.end(), [](const Sprite& lhs, const Sprite& rhs) { return lhs.Transform.Position.y < rhs.Transform.Position.y; });


		//for (const auto& [uiComponent, transformComponent] : componentView)
		//{
		//	if (!uiComponent->IsVisible || !uiComponent->Subtexture)
		//		continue;

		//	const FVector2& scale = transformComponent->Scale;
		//	const float& rotation = transformComponent->Rotation;

		//	float xPosition = transformComponent->Position.x * m_windowSize.x;
		//	xPosition += (scale.x * transformComponent->Pivot.x);

		//	float yPosition = transformComponent->Position.y * m_windowSize.y;
		//	yPosition += (scale.y * transformComponent->Pivot.y);

		//	const auto& [r, g, b, a] = uiComponent->CurrentColor;

		//	spriteBatch.Sprites.emplace_back(Transform{ { xPosition, yPosition, 0.f }, { scale.x, scale.y }, rotation }, glm::vec4{ r, g, b, a }, uiComponent->Subtexture.get());
		//}

		return spriteBatch;
	}
}
