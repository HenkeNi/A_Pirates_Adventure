#include "Pch.h"
#include "SpriteRenderSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"


SpriteRenderSystem::SpriteRenderSystem()
	: System{ 0 }
{
}

SpriteRenderSystem::~SpriteRenderSystem()
{
}

void SpriteRenderSystem::Receive(Message& message)
{
}

void SpriteRenderSystem::Draw() // TODO; should pass along if bash should be flushed in render command?
{
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");

	auto* camera = m_entityManager->FindFirst<CameraComponent>();
	if (!camera)
		return;
	
	auto entities = m_entityManager->FindAll<SpriteComponent, TransformComponent>();
	if (entities.empty())
		return;
	
	auto* cameraComponent = camera->GetComponent<CameraComponent>();
	if (!cameraComponent)
		return;

	std::sort(entities.begin(), entities.end(), [](const Entity* e1, const Entity* e2) {

		auto transform1 = e1->GetComponent<TransformComponent>();
		auto sprite1 = e1->GetComponent<SpriteComponent>();

		auto transform2 = e2->GetComponent<TransformComponent>();
		auto sprite2 = e2->GetComponent<SpriteComponent>();

		// auto pos1 = transform1->CurrentPos.y -

		//float yPos = transform1->CurrentPos.y;
		//float textureSize = sprite1->Subtexture->GetSize().y;
		//float pivot = sprite1->Pivot.y;
		//yPos += sprite1->Subtexture->GetSize().y * sprite1->Pivot.y;


		//return (transform1->CurrentPos.y + (sprite1->Subtexture->GetSize().y * (1.0f - sprite1->Pivot.y))) < (transform2->CurrentPos.y + (sprite2->Subtexture->GetSize().y * sprite2->Pivot.y));

		//return (transform1->CurrentPos.y - sprite1->Subtexture->GetSize().y) < (transform2->CurrentPos.y - sprite2->Subtexture->GetSize().y);
		//return (transform1->CurrentPos.y - (sprite1->Subtexture->GetSize().y * sprite1->Pivot.y)) < (transform2->CurrentPos.y - (sprite2->Subtexture->GetSize().y * sprite2->Pivot.y));

		// TODO: FIX Scale....

		return e1->GetComponent<TransformComponent>()->CurrentPos.y < e2->GetComponent<TransformComponent>()->CurrentPos.y;
		}); // also sort by "bShouldRender"? return when hitting a entity that shouldnt render..

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(entities.size());

	for (const Entity* entity : entities)
	{
		// TODO: Fix by having better filtering... (look into bitset) or check TagComponent
		if (entity->HasComponent<HUDComponent>() || entity->HasComponent<UIComponent>()) 
			continue;

		const auto* spriteComponent = entity->GetComponent<SpriteComponent>();
		const auto* transformComponent = entity->GetComponent<TransformComponent>();

		if (!spriteComponent || !transformComponent)
			continue;

		if (!spriteComponent->ShouldRender)
			continue;

		const auto& subtexture = spriteComponent->Subtexture;
		const auto& color = spriteComponent->CurrentColor;

		glm::vec4 spriteColor = { color.x, color.y, color.z, color.w };

		const auto& [currPos, prevPos, scale, pivot, rotation] = *transformComponent;

		glm::vec3 position;
		position.x = currPos.x + (pivot.x * scale.x);
		position.y = currPos.y + (pivot.y * scale.y);

		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{{ position.x, position.y, 0.f }, { scale.x, scale.y }, rotation }, spriteColor, subtexture);
	}

	spriteBatch.ProjectionMatrix = cameraComponent->Camera.GetViewProjectionMatrix();

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}