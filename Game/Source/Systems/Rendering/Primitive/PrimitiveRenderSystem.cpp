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

		static float offset = 0.4f;

		Hi_Engine::PrimitiveRenderer::GetInstance().Render(Hi_Engine::PrimitiveRenderData{ rect->m_color, rect->m_shader, { position.x, 0.f - offset, position.y }, { scale.x, scale.y }, -90.f });
	}
}
