#include "Pch.h"
#include "MovementSystem.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"

#include "Components/Core/CoreComponents.h"


MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::Receive(Message& aMsg)
{
	// Update collider when game starts?


	// LITEN FOR ENTITY DEATH... (if has falling component... play it? => tree falling...)
}

void MovementSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<TransformComponent, VelocityComponent>();

	for (auto* entity : entities)
	{
		auto* transform = entity->GetComponent<TransformComponent>();
		auto* velocity = entity->GetComponent<VelocityComponent>();

		transform->PreviousPos = transform->CurrentPos;
		transform->CurrentPos += velocity->Speed * velocity->Velocity * aDeltaTime;

		//if (entity->HasComponent<PlayerControllerComponent>())
			//std::cout << "Pos: " << transform->CurrentPos.x << ", " << transform->CurrentPos.y << "\n";

		UpdateColliders(entity, transform, velocity);

		// TODO; update RectComponent?

		// TODO; decrease velocity...
		velocity->Velocity = { 0.f, 0.f, };
	}
}

bool MovementSystem::HasMoved(const Entity* anEntity)
{
	auto transform = anEntity->GetComponent<TransformComponent>();
	return transform->CurrentPos != transform->PreviousPos;
}

void MovementSystem::UpdateColliders(Entity* anEntity, TransformComponent* aTransformComponent, VelocityComponent* aVelocityComponent)
{
	if (auto* attackCollider = anEntity->GetComponent<AttackComponent>())
	{
		const auto& velocity = aVelocityComponent->Velocity;

		auto& aabb	 = attackCollider->Collider;
		auto& offset = attackCollider->Offset;

		// Update collider offset
		auto colliderWidth = aabb.GetWidth();

		offset.x = velocity.x > 0.f ? colliderWidth : velocity.x < 0.f ? -colliderWidth : 0;
		offset.y = velocity.y > 0.f ? colliderWidth : velocity.y < 0.f ? -colliderWidth : 0;
		//offset.z = velocity.z > 0.f ? colliderWidth : velocity.z < 0.f ? -colliderWidth : 0;
		
		// Update collider position
		const auto position = aTransformComponent->CurrentPos + attackCollider->Offset;

		float halfWidth  = aabb.GetWidth()  * 0.5f;
		float halfHeight = aabb.GetHeight() * 0.5f;

		aabb.Init({ position.x - halfWidth, position.y - halfHeight }, { position.x + halfWidth, position.y + halfHeight });
	}

	if (auto* hitboxCollider = anEntity->GetComponent<HitboxComponent>())
	{
		auto& aabb = hitboxCollider->Collider;
		const auto position = aTransformComponent->CurrentPos;

		float halfWidth = aabb.GetWidth() * 0.5f;
		float halfHeight = aabb.GetHeight() * 0.5f;

		aabb.Init({ position.x - halfWidth, position.y - halfHeight }, { position.x + halfWidth, position.y + halfHeight });
	}
}