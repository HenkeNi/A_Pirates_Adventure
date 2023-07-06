#include "Pch.h"
#include "PrimitiveRenderSystem.h"
#include "EntityManager.h"
#include "Rendering/RenderComponents.h"
#include "Core/CoreComponents.h"
#include "Combat/CombatComponents.h"

PrimitiveRenderSystem::PrimitiveRenderSystem()
{
}

PrimitiveRenderSystem::~PrimitiveRenderSystem()
{
}

void PrimitiveRenderSystem::Receive(Message& aMsg)
{
}

void PrimitiveRenderSystem::Draw()
{ 
	if (!m_entityManager)
		return;

	//auto entities = m_entityManager->FindAllWithComponents<RectComponent, TransformComponent>(); // Don't just get Rect components??
	auto entities = m_entityManager->FindAllWithComponents<RectComponent, AttackColliderComponent>(); // Don't just get Rect components??

	for (const Entity* entity : entities)
	{
		//const auto* transform	= entity->GetComponent<TransformComponent>();
		const auto* attackComponent	= entity->GetComponent<AttackColliderComponent>();
		const auto* rect			= entity->GetComponent<RectComponent>();
	
		const auto& collider = attackComponent->m_collider;
		//const auto& position	= transform->m_currentPos;
		const auto& position			= collider.GetCenter();
		const CU::Vector2<float>& scale = { collider.GetWidth(), collider.GetHeight() };

		static float offset = -0.1f;	// Don't do this here... just fo rendering...

		Hi_Engine::PrimitiveRenderer::GetInstance().Render(Hi_Engine::PrimitiveRenderData{ rect->m_color, rect->m_shader, { position.x, 0.f - offset, position.y }, { scale.x, scale.y }, -90.f });
	}






	auto otherEntities = m_entityManager->FindAllWithComponents<RectComponent, HitboxColliderComponent>();
	for (const Entity* entity : otherEntities)
	{
		const auto* hitboxComponent = entity->GetComponent<HitboxColliderComponent>();
		const auto* rect = entity->GetComponent<RectComponent>();

		const auto& collider = hitboxComponent->m_collider;
		const auto& position = collider.GetCenter();

		static float offset = -0.1f;
		const CU::Vector2<float>& scale = { collider.GetWidth(), collider.GetHeight() };

		Hi_Engine::PrimitiveRenderer::GetInstance().Render(Hi_Engine::PrimitiveRenderData{ rect->m_color, rect->m_shader, { position.x, 0.f - offset, position.y }, { scale.x, scale.y }, -90.f });
	}
}