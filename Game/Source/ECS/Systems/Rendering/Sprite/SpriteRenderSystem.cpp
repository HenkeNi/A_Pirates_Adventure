#include "Pch.h"
#include "SpriteRenderSystem.h"
#include "Components/Core/CoreComponents.h"
#include "Components/UI/UIComponents.h"
// #include "Components/ComponentManager.h"
#include "ECS/ECS.h"


SpriteRenderSystem::SpriteRenderSystem()
	: System{ 0 }
{
}

SpriteRenderSystem::~SpriteRenderSystem()
{
}

void SpriteRenderSystem::Draw() // TODO; should pass along if bash should be flushed in render command?
{
	assert(m_ecs && "ERROR: ECS is nullptr!");

	auto camera = m_ecs->FindEntity(m_signatures.at("Camera"));
	if (!camera.has_value())
		return;
	
	auto sprites = m_ecs->FindEntities(m_signatures.at("Sprites"));
	if (sprites.empty())
		return;
	
	std::vector<Entity> renderableSprites;
	
	std::copy_if(sprites.begin(), sprites.end(), std::back_inserter(renderableSprites), [&](Entity entity)
		{
			auto* spriteComponent = m_ecs->GetComponent<SpriteComponent>(entity);
			return spriteComponent->ShouldRender;
		});
	

	std::sort(renderableSprites.begin(), renderableSprites.end(), [&](Entity lhs, Entity rhs)
		{
			auto lhsTransform = m_ecs->GetComponent<TransformComponent>(lhs);
			auto rhsTransform = m_ecs->GetComponent<TransformComponent>(rhs);

			auto lhsSprite = m_ecs->GetComponent<SpriteComponent>(lhs);
			auto rhsSprite = m_ecs->GetComponent<SpriteComponent>(rhs);

			return lhsTransform->CurrentPos.y < rhsTransform->CurrentPos.y;
			
			//float lhsPositionY = lhsTransform->CurrentPos.y;
			//lhsPositionY - lhsTransform->Scale.y * lhsTransform->Pivot.y;

			//float rhsPositionY = rhsTransform->CurrentPos.y;
			//rhsPositionY - rhsTransform->Scale.y * rhsTransform->Pivot.y;

			//return lhsPositionY < rhsPositionY;			
		}); // also sort by "bShouldRender"? return when hitting a entity that shouldnt render..

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(renderableSprites.size());

	for (Entity sprite : renderableSprites)
	{
		// TODO: Fix by having better filtering... check TagComponent
		if (m_ecs->GetComponent<HUDComponent>(sprite) || m_ecs->GetComponent<UIComponent>(sprite))
			continue;

		const auto* spriteComponent = m_ecs->GetComponent<SpriteComponent>(sprite);
		const auto* transformComponent = m_ecs->GetComponent<TransformComponent>(sprite);

		if (!spriteComponent || !transformComponent) // needed??
			continue;

	//	if (!spriteComponent->ShouldRender)
		//	continue;

		const auto& subtexture = spriteComponent->Subtexture;
		const auto& color = spriteComponent->CurrentColor;

		glm::vec4 spriteColor = { color.x, color.y, color.z, color.w };

		const auto& [currPos, prevPos, scale, pivot, rotation] = *transformComponent;

		glm::vec3 position;
		position.x = currPos.x + (pivot.x * scale.x);
		position.y = currPos.y + (pivot.y * scale.y);

		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{{ position.x, position.y, 0.f }, { scale.x, scale.y }, rotation }, spriteColor, subtexture);
	}



	auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(camera.value());
	if (!cameraComponent)
		return;

	spriteBatch.ProjectionMatrix = cameraComponent->Camera.GetViewProjectionMatrix();

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}

void SpriteRenderSystem::SetSignature()
{
	m_signatures.insert({ "Camera", m_ecs->GetSignature<CameraComponent>() });
	m_signatures.insert({ "Sprites", m_ecs->GetSignature<SpriteComponent, TransformComponent>() });
}