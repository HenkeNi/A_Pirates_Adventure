#include "Pch.h"
#include "MovementSystem.h"
#include "Entity.h"
#include "EntityManager.h"

#include "Core/CoreComponents.h"
#include "Physics/PhysicsComponents.h"
#include "Combat/CombatComponents.h"
#include "Rendering/RenderComponents.h"


MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::Receive(Message& aMsg)
{
}

void MovementSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAllWithComponents<TransformComponent, VelocityComponent>();

	for (auto* entity : entities)
	{
		auto* transform = entity->GetComponent<TransformComponent>();
		auto* velocity = entity->GetComponent<VelocityComponent>();

		transform->m_previousPos = transform->m_currentPos;

		transform->m_currentPos += velocity->m_velocity * aDeltaTime;
		velocity->m_velocity += velocity->m_acceleration * aDeltaTime;


		if (auto* attackCollider = entity->GetComponent<AttackColliderComponent>())
		{
			auto& aabb				= attackCollider->m_collider;
			const auto newPosition	= transform->m_currentPos + attackCollider->m_offset;

			float halfWidth		= aabb.GetWidth() * 0.5f;
			float halfHeight	= aabb.GetHeight() * 0.5f;

			attackCollider->m_collider.Init({ newPosition.x - halfWidth, newPosition.z - halfHeight }, { newPosition.x + halfWidth, newPosition.z + halfHeight });
		}

		if (auto* rect = entity->GetComponent<RectComponent>())
		{
			// Have primitive shapes in Engine instead??
			
		}

	}

}

bool MovementSystem::HasMoved(class TransformComponent* aTransform) const
{
	bool hasMoved = aTransform->m_currentPos != aTransform->m_previousPos;
	return hasMoved;
}