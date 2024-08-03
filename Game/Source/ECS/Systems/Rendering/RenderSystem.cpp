#include "Pch.h"
#include "RenderSystem.h"
#include "ECS.h"


RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Draw()
{ 
	auto entity = m_ecs->FindEntity(m_signatures.at("Camera"));
	if (!entity.has_value())
		return;

	Entity camera = entity.value();
	
	RenderText(camera);

#ifdef DEBUG

	RenderScreenSpaceColliders(camera); // FIX!
	RenderDebugColliders(camera);
	
#endif // DEBUG

	RenderSprites(camera);
	RenderMap(camera);
}

void RenderSystem::SetSignature()
{
	// Todo; fetch archetypes instead?
	m_signatures.insert({ "Camera", m_ecs->GetSignature<CameraComponent>() });
	m_signatures.insert({ "Sprites", m_ecs->GetSignature<SpriteComponent, TransformComponent>() });
	m_signatures.insert({ "Text", m_ecs->GetSignature<TextComponent, TransformComponent>() });

#ifdef DEBUG

	m_signatures.insert({ "Debug", m_ecs->GetSignature<ColliderComponent, TransformComponent>() });

#endif // DEBUG
}

void RenderSystem::RenderMap(Entity camera)
{
	auto mapChunkComponents = m_ecs->GetComponents<MapChunkComponent>();

	if (mapChunkComponents.empty())
		return;

	// TODO; sort out map chunks out of view... have a bounds component??

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(mapChunkComponents.size());

	for (auto* mapChunkComponent : mapChunkComponents)
	{
		if (!mapChunkComponent)
			continue;

		std::copy(mapChunkComponent->Sprites.begin(), mapChunkComponent->Sprites.end(), std::back_inserter(spriteBatch.Sprites));
	}

	auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(camera);
	if (!cameraComponent)
		return;

	spriteBatch.ProjectionMatrix = cameraComponent->Camera.GetViewProjectionMatrix();
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}

void RenderSystem::RenderSprites(Entity camera)
{
	auto entities = m_ecs->FindEntities(m_signatures.at("Sprites"));
	if (entities.empty())
		return;

	std::vector<Entity> sprites;
	sprites.reserve(entities.size());

	std::vector<Entity> uiElements;
	uiElements.reserve(entities.size());

	std::vector<Entity> hudElements;
	hudElements.reserve(entities.size());

	for (auto entity : entities)
	{
		auto* spriteComponent = m_ecs->GetComponent<SpriteComponent>(entity);
		if (!spriteComponent->ShouldRender)
			continue;

		if (m_ecs->GetComponent<HUDComponent>(entity))
			hudElements.push_back(entity);
		else if (m_ecs->GetComponent<UIComponent>(entity))
			uiElements.push_back(entity);
		else
			sprites.push_back(entity);
	}

	auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(camera);
	if (!cameraComponent)
		return;

#pragma region UI_Rendering

	/* Render UI */
	std::sort(uiElements.begin(), uiElements.end(), [&](Entity e1, Entity e2)
		{
			const auto* u1 = m_ecs->GetComponent<UIComponent>(e1);
			const auto* u2 = m_ecs->GetComponent<UIComponent>(e2);

			return u1->RenderDepth > u2->RenderDepth;
		});

	uiElements.insert(uiElements.end(), hudElements.begin(), hudElements.end());

	Hi_Engine::SpriteBatch uiElementBatch;
	uiElementBatch.Sprites.reserve(uiElements.size());

	auto windowSize = Hi_Engine::ServiceLocator::GetWindow().lock()->GetSize();

	for (auto entity : uiElements)
	{
		const auto& [defaultColor, currentColor, subtexture, shouldRender] = *m_ecs->GetComponent<SpriteComponent>(entity);
		const auto& [currPos, prevPos, scale, pivot, rotation] = *m_ecs->GetComponent<TransformComponent>(entity);

		const auto& [r, g, b, a] = currentColor;

		float xPosition = currPos.x * windowSize.x;
		xPosition += (scale.x * pivot.x);

		float yPosition = currPos.y * windowSize.y;
		yPosition += (scale.y * pivot.y);

		uiElementBatch.Sprites.emplace_back(Hi_Engine::Transform{ { xPosition, yPosition, 0.f }, { scale.x, scale.y }, rotation }, glm::vec4{ r, g, b, a }, subtexture);
	}

	uiElementBatch.ProjectionMatrix = cameraComponent->Camera.GetProjectionMatrix();
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(uiElementBatch);

#pragma endregion UI_Rendering

#pragma region Sprite_Rendering

	std::sort(sprites.begin(), sprites.end(), [&](Entity lhs, Entity rhs)
		{
			auto lhsTransform = m_ecs->GetComponent<TransformComponent>(lhs);
			auto rhsTransform = m_ecs->GetComponent<TransformComponent>(rhs);

			auto lhsSprite = m_ecs->GetComponent<SpriteComponent>(lhs);
			auto rhsSprite = m_ecs->GetComponent<SpriteComponent>(rhs);

			return lhsTransform->CurrentPos.y < rhsTransform->CurrentPos.y;
		});

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(sprites.size());

	/* Render sprites */
	for (Entity sprite : sprites)
	{
		const auto& [defaultColor, currentColor, subtexture, shouldRender] = *m_ecs->GetComponent<SpriteComponent>(sprite);
		const auto& [currPos, prevPos, scale, pivot, rotation] = *m_ecs->GetComponent<TransformComponent>(sprite);

		glm::vec4 spriteColor = { currentColor.x, currentColor.y, currentColor.z, currentColor.w };

		glm::vec3 position;
		position.x = currPos.x + (pivot.x * scale.x);
		position.y = currPos.y + (pivot.y * scale.y);

		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { position.x, position.y, 0.f }, { scale.x, scale.y }, rotation }, spriteColor, subtexture);
	}

	spriteBatch.ProjectionMatrix = cameraComponent->Camera.GetViewProjectionMatrix();
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);

#pragma endregion Sprite_Rendering

}

void RenderSystem::RenderText(Entity camera)
{
	assert(m_ecs && "[TextRenderSystem - ERROR]: ECS is nullptr!");

	return;

	// DO in initilaizcomponent instead
	auto* shader = &Hi_Engine::ResourceHolder<Hi_Engine::GLSLShader>::GetInstance().GetResource("Text"); // FIX!! set in Renderer before...

	const auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(camera);
	auto projectionMatrix = cameraComponent->Camera.GetProjectionMatrix();

	auto entities = m_ecs->FindEntities(m_signatures["Text"]);

	for (Entity entity : entities)
	{
		const auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);
		const auto* textComponent = m_ecs->GetComponent<TextComponent>(entity);

		const auto& [currentPos, previousPos, scale, pivot, rotation] = *transformComponent;
		const auto& [text, color, size, alignment, font] = *textComponent;

		FVector2 position;
		position.x = currentPos.x + (pivot.x * size);
		position.y = currentPos.y + (pivot.y * size);

		Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::TextRenderEvent>(Hi_Engine::TextRenderData{ shader, font, (float)1.f, color, position, text, alignment }, projectionMatrix);
	}
}

void RenderSystem::RenderDebugColliders(Entity camera)
{
	auto entities = m_ecs->FindEntities(m_signatures["Debug"]);
	if (entities.empty())
		return;

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(entities.size());


	// draw triggers and colliders in different colors. 
	auto* texture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "debug", 0, 0 });

	for (auto entity : entities)
	{
		// TODO; signature that entity should contain!?

		if (m_ecs->GetComponent<UIComponent>(entity) || m_ecs->GetComponent<HUDComponent>(entity))
			continue;

		auto* collider = m_ecs->GetComponent<ColliderComponent>(entity);

		const auto& position = collider->Collider.GetCenter();
		const auto& scale = collider->Collider.GetSize();

		glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };
		
		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { position.x, position.y, 0.f }, { scale.x, scale.y }, 0.f }, color, texture);
	}

	auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(camera);

	spriteBatch.ProjectionMatrix = cameraComponent->Camera.GetViewProjectionMatrix();
	
	// uiBatch.ProjectionMatrix = cameraComponent->Camera.GetProjectionMatrix();
	// RENDER FUSTRUM
	//auto* cameraComponent = camera->GetComponent<CameraComponent>();
	//const auto& position = cameraComponent->Frustum.GetCenter();
	//const auto& scale = cameraComponent->Frustum.GetSize();
	//
	//auto* texture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource("debug_00");

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}

void RenderSystem::RenderScreenSpaceColliders(Entity camera)
{
	auto entities = m_ecs->FindEntities(m_signatures["Debug"]);
	if (entities.empty())
		return;

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(entities.size());

	auto* texture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "debug", 0, 0 });

	for (auto entity : entities)
	{
		//if (!entity->HasComponent<UIComponent>() || !entity->HasComponent<HUDComponent>())
		if (!m_ecs->HasComponent<UIComponent>(entity))
			continue;

		auto* colliderComponent = m_ecs->GetComponent<ColliderComponent>(entity);

		const auto& position = colliderComponent->Collider.GetCenter();
		const auto& scale = colliderComponent->Collider.GetSize();

		//const auto& [currPos, prevPos, scale, pivot, rotation] = *transformComponent;
		//const auto& [r, g, b, a] = spriteComponent->CurrentColor;

		static const float windowWidth = 1400.f;
		float xPosition = position.x * windowWidth;
		//xPosition += (scale.x * pivot.x);

		static const float windowHeight = 800.f;
		float yPosition = position.y * windowHeight;

		//yPosition += (scale.y * pivot.y);

		glm::vec4 color = { 0.4f, 0.2f, 0.6f, 1.f };

		//spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { xPosition, yPosition, 0.f }, { scale.x * windowWidth, scale.y * windowHeight }, 0.f }, color, texture);
		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { xPosition, yPosition, 0.f }, { scale.x, scale.y }, 0.f }, color, texture);
	}

	spriteBatch.ProjectionMatrix = m_ecs->GetComponent<CameraComponent>(camera)->Camera.GetProjectionMatrix();

	// RENDER FUSTRUM
	//auto* cameraComponent = camera->GetComponent<CameraComponent>();
	//const auto& position = cameraComponent->Frustum.GetCenter();
	//const auto& scale = cameraComponent->Frustum.GetSize();
	//
	//auto* texture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource("debug_00");

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}