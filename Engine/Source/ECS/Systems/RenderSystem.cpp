#include "Pch.h"
#include "RenderSystem.h"
#include "Services/Rendering/RenderService.h"
#include "Services/Window/WindowService.h"
#include "ECS/Components/CoreComponents.h"
#include "ECS/World/World.h"

#include "ECS/Utility/EntityHandle.h"

#include "Services/ServiceRegistry.h"

#include "Services/Rendering/Subtexture2D.h"
#include "Services/Resource/ResourceService.h"
#include "Services/Resource/ResourceAliases.h"

namespace Hi_Engine
{
	RenderSystem::RenderSystem(World& world, ServiceRegistry& registry)
	: System{ world }, m_renderService{ registry.TryGetWeak<RenderService>() }, m_subtextureAssetService{ registry.TryGetWeak<SubtextureAssetService>() }, m_windowSize{ registry.Get<WindowService>().GetSize() }
	{
	}

	void RenderSystem::OnEvent(WindowEvent& event)
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

		auto renderService = m_renderService.lock();
		if (!renderService)
		{
			Logger::LogWarning("[RenderSystem::Update] - No valid renderer!");
			return;
		}

		auto assetService = m_subtextureAssetService.lock();
		if (!assetService)
		{
			Logger::LogWarning("[RenderSystem::Update] - No valid subtexture asset service!");
			return;
		}

		renderService->BeginFrame();
		renderService->ClearScreen(); // or have part of the process function call?

		auto cameraView = m_world.GetComponentView<CameraComponent>(); // TODO; use FindIf fnc later...
		auto cameraEntity = cameraView.FindIf([&](CameraComponent& component) { return component.IsActive; }); // return pair?

		if (!cameraEntity.has_value())
		{
			Logger::LogWarning("[RenderSystem::Update] - Failed to find an active Camera!");
			return;
		}

		auto& cameraComponent = m_world.GetComponent<CameraComponent>(cameraEntity.value());
		const auto& camera = cameraComponent.Camera;

		RenderWorldSprites(*assetService, *renderService, camera.GetViewProjectionMatrix());

		RenderUISprites(*assetService, *renderService, camera.GetProjectionMatrix());

		renderService->EndFrame();
	}

	eUpdatePhase RenderSystem::GetUpdatePhase() const
	{
		return eUpdatePhase::PostUpdate;
	}

	void RenderSystem::RenderWorldSprites(SubtextureHolder& textureHolder, RenderService& renderService, const glm::mat4& projection)
	{
		auto componentView = m_world.GetComponentView<SpriteComponent, TransformComponent>(
			[](EntityHandle handle)
			{
				return !handle.HasAnyComponents<UIComponent>();
			});

		SpriteBatch spriteBatch;
		spriteBatch.Sprites.reserve(componentView.Size());

		componentView.ForEach([&](const SpriteComponent& spriteComponent, const TransformComponent& transformComponent)
			{
				if (!spriteComponent.IsVisible)
					return;

				const FVector2& scale = transformComponent.Scale;
				const float& rotation = transformComponent.Rotation;

				float xPos = transformComponent.Position.x + (transformComponent.Pivot.x * scale.x);
				float yPos = transformComponent.Position.y + (transformComponent.Pivot.y * scale.y);

				const auto& [r, g, b, a] = spriteComponent.CurrentColor;

				const auto& [id, coords] = spriteComponent.TextureData;
				auto subtexture = textureHolder.GetResource(SubtextureData{ id, coords.x, coords.y });

				spriteBatch.Sprites.emplace_back(Transform{ { xPos, yPos, 0.f }, { scale.x, scale.y }, transformComponent.Rotation }, glm::vec4{ r, g, b, a }, subtexture.get());
			});

		auto& sprites = spriteBatch.Sprites;
		std::sort(sprites.begin(), sprites.end(), [](const Sprite& lhs, const Sprite& rhs) { return lhs.Transform.Position.y < rhs.Transform.Position.y; });

		if (!spriteBatch.Sprites.empty())
		{
			renderService.SetProjectionMatrix(projection); // do in function?? Check if any entities to draw before?!

			renderService.AddSpriteBatch(std::move(spriteBatch));
			{
				PROFILE_FUNCTION("RenderSystem Process batch 1");
				renderService.ProcessBatches();
			}
		}
	}

	void RenderSystem::RenderUISprites(SubtextureHolder& textureHolder, RenderService& renderService, const glm::mat4& projection)
	{
		auto componentView = m_world.GetComponentView<SpriteComponent, TransformComponent>(
			[](EntityHandle handle)
			{
				return handle.HasAnyComponents<UIComponent>();
			});

		SpriteBatch spriteBatch;
		spriteBatch.Sprites.reserve(componentView.Size());

		componentView.ForEach([&](const SpriteComponent& spriteComponent, const TransformComponent& transformComponent)
			{
				if (!spriteComponent.IsVisible)
					return;

				const FVector2& scale = transformComponent.Scale;
				const float& rotation = transformComponent.Rotation;

				float xPos = transformComponent.Position.x * m_windowSize.x;
				xPos += (scale.x * transformComponent.Pivot.x);

				float yPos = transformComponent.Position.y * m_windowSize.y;
				yPos += (scale.y * transformComponent.Pivot.y);

				const auto& [r, g, b, a] = spriteComponent.CurrentColor;

				const auto& [id, coords] = spriteComponent.TextureData;
				auto subtexture = textureHolder.GetResource(SubtextureData{ id, coords.x, coords.y });

				spriteBatch.Sprites.emplace_back(Transform{ { xPos, yPos, 0.f }, { scale.x, scale.y }, rotation }, glm::vec4{ r, g, b, a }, subtexture.get());
			});

		// Will this work when it should be render depth?? -> maybe solution is to use render depth for z or something
		auto& sprites = spriteBatch.Sprites;
		std::sort(sprites.begin(), sprites.end(), [](const Sprite& lhs, const Sprite& rhs) { return lhs.Transform.Position.y < rhs.Transform.Position.y; });


		if (!spriteBatch.Sprites.empty())
		{
			renderService.SetProjectionMatrix(projection);

			renderService.AddSpriteBatch(std::move(spriteBatch));
			renderService.ProcessBatches();
		}
	}
}
