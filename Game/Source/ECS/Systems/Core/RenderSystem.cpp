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
	assert(m_ecs && "[RenderSystem::Draw] - ECS is not initialized!");

	auto entity = m_ecs->FindEntity(m_signatures.at("Camera"));
	if (!entity.has_value())
		return;

	auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(entity.value());
	if (!cameraComponent)
		return;

	auto& camera = cameraComponent->Camera;

	const auto projectionMatrix = camera.GetProjectionMatrix();

#ifdef DEBUG

	RenderUIBoundingBoxes(projectionMatrix); // FIX!

#endif // DEBUG

	RenderText(projectionMatrix);
	RenderUI(projectionMatrix);

	const auto viewProjectionMatrix = camera.GetViewProjectionMatrix();

#ifdef DEBUG

	//RenderDebugColliders(camera);
	RenderPhysicsColliders(viewProjectionMatrix);

#endif // DEBUG

	RenderEntities(viewProjectionMatrix);
	RenderMapChunks(viewProjectionMatrix);
}

void RenderSystem::SetSignature()
{
	// Todo; fetch archetypes instead?
	m_signatures.insert({ "Camera", m_ecs->GetSignature<CameraComponent>() });
	m_signatures.insert({ "Entities", m_ecs->GetSignature<SpriteComponent, TransformComponent>() });
	
	m_signatures.insert({ "Text", m_ecs->GetSignature<TextComponent, TransformComponent>() });
	m_signatures.insert({ "UI", m_ecs->GetSignature<UIComponent, TransformComponent>() });

#ifdef DEBUG

	m_signatures.insert({ "Debug", m_ecs->GetSignature<BoundingBoxComponent, TransformComponent>() }); // not needed?? use ui component instead?

#endif // DEBUG
}


void RenderSystem::RenderDebugColliders(Entity camera)
{
	auto entities = m_ecs->FindEntities(m_signatures["Debug"]);
	if (entities.empty())
		return;

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(entities.size());


	// draw triggers and colliders in different colors. 
	auto texture = Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "debug", 0, 0 });

	for (auto entity : entities)
	{
		// TODO; signature that entity should contain!?

		if (m_ecs->GetComponent<UIComponent>(entity) || m_ecs->GetComponent<HUDComponent>(entity))
			continue;

		auto* collider = m_ecs->GetComponent<ColliderComponent>(entity);

		const auto& position = collider->Collider.GetCenter();
		const auto& scale = collider->Collider.GetSize();

		glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };
		
		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { position.x, position.y, 0.f }, { scale.x, scale.y }, 0.f }, color, texture.get());
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

	Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}

void RenderSystem::RenderUIBoundingBoxes(const glm::mat4& proj)
{
	auto entities = m_ecs->FindEntities(m_signatures["UI"]);
	
	if (entities.empty())
		return;

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(entities.size());

	auto texture = Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "debug", 0, 0 });

	for (auto entity : entities)
	{
		if (!m_ecs->HasComponent<BoundingBoxComponent>(entity)) // FIX!
			continue;

		auto* boundingBoxComponent = m_ecs->GetComponent<BoundingBoxComponent>(entity);
		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);

		const auto& position = boundingBoxComponent->Bounds.GetCenter();
		const auto& scale = boundingBoxComponent->Bounds.GetSize();


		static const float windowWidth = 1400.f;
		float xPosition = position.x * windowWidth;
		//xPosition += (scale.x * pivot.x);

		static const float windowHeight = 800.f;
		float yPosition = position.y * windowHeight;

		float scaleX = scale.x * windowWidth;
		float scaleY = scale.y * windowHeight;

		//yPosition += (scale.y * pivot.y);

		glm::vec4 color = { 0.4f, 0.2f, 0.6f, 1.f };

		//spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { xPosition, yPosition, 0.f }, { scale.x * windowWidth, scale.y * windowHeight }, 0.f }, color, texture);
		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { xPosition, yPosition, 0.f }, { scaleX, scaleY }, 0.f }, color, texture.get());
	}

	spriteBatch.ProjectionMatrix = proj;

	// RENDER FUSTRUM
	//auto* cameraComponent = camera->GetComponent<CameraComponent>();
	//const auto& position = cameraComponent->Frustum.GetCenter();
	//const auto& scale = cameraComponent->Frustum.GetSize();
	//
	//auto* texture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource("debug_00");

	Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}

void RenderSystem::RenderPhysicsColliders(const glm::mat4& proj)
{
	auto physicsComponents = m_ecs->GetComponents<PhysicsComponent>();

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(physicsComponents.size());

	auto texture = Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "debug", 0, 0 });

	for (const auto& physicsComponent : physicsComponents)
	{
		const auto& body = physicsComponent.PhysicsBody;
		const auto& position = body.GetPosition();
		const auto& scale = body.GetSize();

		glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };

		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { position.x, position.y, 0.f }, { scale.x, scale.y }, 0.f }, color, texture.get());
	}

	spriteBatch.ProjectionMatrix = proj;
	Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}

void RenderSystem::RenderMapChunks(const glm::mat4& proj)
{
	auto& mapChunkComponents = m_ecs->GetComponents<MapChunkComponent>();

	if (mapChunkComponents.empty())
		return;

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(mapChunkComponents.size());

	for (auto& mapChunkComponent : mapChunkComponents)
	{
		if (mapChunkComponent.IsVisible)
		{
			std::copy(mapChunkComponent.Sprites.begin(), mapChunkComponent.Sprites.end(), std::back_inserter(spriteBatch.Sprites));
		}
	}

	spriteBatch.ProjectionMatrix = proj;
	Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}

void RenderSystem::RenderEntities(const glm::mat4& proj)
{
	auto entities = m_ecs->FindEntities(m_signatures.at("Entities"));

	if (entities.empty())
		return;

	std::sort(entities.begin(), entities.end(), [&](Entity lhs, Entity rhs)
		{
			const auto* lhsTransform = m_ecs->GetComponent<TransformComponent>(lhs);
			const auto* rhsTransform = m_ecs->GetComponent<TransformComponent>(rhs);

			if (!lhsTransform || !rhsTransform)
				return false;

			return lhsTransform->CurrentPos.y < rhsTransform->CurrentPos.y;
		});

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(entities.size());

	for (Entity entity : entities)
	{
		const auto* spriteComponent = m_ecs->GetComponent<SpriteComponent>(entity);

		if (!spriteComponent->IsVisible)
			continue;

		const auto& [currPos, prevPos, scale, pivot, rotation] = *m_ecs->GetComponent<TransformComponent>(entity);

		glm::vec4 spriteColor = { spriteComponent->CurrentColor.x, spriteComponent->CurrentColor.y, spriteComponent->CurrentColor.z, spriteComponent->CurrentColor.w };

		glm::vec3 position;
		position.x = currPos.x + (pivot.x * scale.x);
		position.y = currPos.y + (pivot.y * scale.y);

		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { position.x, position.y, 0.f }, { scale.x, scale.y }, rotation }, spriteColor, spriteComponent->Subtexture.get());
	}

	spriteBatch.ProjectionMatrix = proj;
	Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}

void RenderSystem::RenderText(const glm::mat4& proj)
{
	assert(m_ecs && "[TextRenderSystem - ERROR]: ECS is nullptr!");

	return;

	// DO in initilaizcomponent instead
	auto shader = Hi_Engine::ResourceHolder<Hi_Engine::GLSLShader>::GetInstance().GetResource("Text"); // FIX!! set in Renderer before...

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

		// Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::TextRenderEvent>(Hi_Engine::TextRenderData{ shader, font, (float)1.f, color, position, text, alignment }, proj);
	}
}

void RenderSystem::RenderUI(const glm::mat4& proj)
{
	auto entities = m_ecs->FindEntities(m_signatures.at("UI"));

	std::sort(entities.begin(), entities.end(), [&](Entity lhs, Entity rhs)
		{
			auto lhsUI = m_ecs->GetComponent<UIComponent>(lhs);
			auto rhsUI = m_ecs->GetComponent<UIComponent>(rhs);
	
			return lhsUI->RenderDepth > rhsUI->RenderDepth;
		});

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(entities.size());

	auto windowSize = Hi_Engine::ServiceLocator::GetWindow().lock()->GetSize();

	for (auto entity : entities)
	{
		const auto& [subtexture, defaultColor, currentColor, depth, shouldRender] = *m_ecs->GetComponent<UIComponent>(entity);
		const auto& [currPos, prevPos, scale, pivot, rotation] = *m_ecs->GetComponent<TransformComponent>(entity);

		const auto& [r, g, b, a] = currentColor;

		float xPosition = currPos.x * windowSize.x;
		xPosition += (scale.x * pivot.x);

		float yPosition = currPos.y * windowSize.y;
		yPosition += (scale.y * pivot.y);

		// todo; valid check subtexture...
		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { xPosition, yPosition, 0.f }, { scale.x, scale.y }, rotation }, glm::vec4{ r, g, b, a }, subtexture.get());
	}

	spriteBatch.ProjectionMatrix = proj;
	Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}
