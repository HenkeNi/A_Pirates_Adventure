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
	// Update collider when game starts?
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
		transform->m_currentPos += velocity->m_speed * velocity->m_velocity * aDeltaTime;

		UpdateColliders(entity, transform, velocity);

		// TODO; update RectComponent?

		// TODO; decrease velocity...
		velocity->m_velocity = { 0.f, 0.f, 0.f };
	}
}

bool MovementSystem::HasMoved(const Entity* anEntity)
{
	auto transform = anEntity->GetComponent<TransformComponent>();
	return transform->m_currentPos != transform->m_previousPos;
}

void MovementSystem::UpdateColliders(Entity* anEntity, TransformComponent* aTransformComponent, VelocityComponent* aVelocityComponent)
{
	if (auto* attackCollider = anEntity->GetComponent<AttackColliderComponent>())
	{
		const auto& velocity = aVelocityComponent->m_velocity;

		auto& aabb	 = attackCollider->m_collider;
		auto& offset = attackCollider->m_offset;

		// Update collider offset
		auto colliderWidth = aabb.GetWidth();

		offset.x = velocity.x > 0.f ? colliderWidth : velocity.x < 0.f ? -colliderWidth : 0;
		offset.z = velocity.z > 0.f ? colliderWidth : velocity.z < 0.f ? -colliderWidth : 0;
		
		// Update collider position
		const auto position = aTransformComponent->m_currentPos + attackCollider->m_offset;

		float halfWidth  = aabb.GetWidth()  * 0.5f;
		float halfHeight = aabb.GetHeight() * 0.5f;

		aabb.Init({ position.x - halfWidth, position.z - halfHeight }, { position.x + halfWidth, position.z + halfHeight });
	}
}