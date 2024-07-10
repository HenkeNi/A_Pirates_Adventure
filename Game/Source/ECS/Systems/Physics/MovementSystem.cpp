#include "Pch.h"
#include "MovementSystem.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"


MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::Receive(Message& message)
{
	// TODO: listen to collision resolved event (from collision system) => update subentities?
}

void MovementSystem::Update(float deltaTime)
{
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");

	auto entities = m_entityManager->FindAll<TransformComponent, VelocityComponent>();

	for (auto* entity : entities)
	{
		if (entity->HasComponent<KnockbackComponent>())
		{
			ApplyKnockback(entity);
		}

		auto* transformComponent = entity->GetComponent<TransformComponent>();
		auto* velocityComponent = entity->GetComponent<VelocityComponent>();

		transformComponent->PreviousPos = transformComponent->CurrentPos;

		auto& velocity = velocityComponent->Velocity;
		if (!Hi_Engine::Math::IsNearlyEqual(velocity.x, 0.f) && !Hi_Engine::Math::IsNearlyEqual(velocity.y, 0.f))
			velocityComponent->Velocity.Normalize();

		transformComponent->CurrentPos += velocityComponent->Speed * velocityComponent->Velocity * deltaTime;

		if (!velocityComponent->IsVelocityConstant)
			velocityComponent->Velocity = { 0.f, 0.f, };

		if (HasMoved(entity))
			MoveSubEntities	(entity);
	}
}

bool MovementSystem::HasMoved(const Entity* entity)
{
	auto transform = entity->GetComponent<TransformComponent>();
	return transform->CurrentPos != transform->PreviousPos;
}

bool MovementSystem::IsKnockbacked(Entity* entity)
{
	if (auto* knockbackComponent = entity->GetComponent<KnockbackComponent>())
	{
		double currentTime = Hi_Engine::Engine::GetTimer().GetTotalTime();
		double knockbackEndTime = knockbackComponent->Timestamp + knockbackComponent->Duration;

		return knockbackEndTime > currentTime;
	}

	return false;
}

void MovementSystem::MoveSubEntities(Entity* entity)
{
	// HERE? or in Transform System?
	if (auto* childComponent = entity->GetComponent<SubEntitiesComponent>())
	{
		auto* transformComponent = entity->GetComponent<TransformComponent>();

		for (unsigned entityID : childComponent->IDs)
		{
			if (auto* child = m_entityManager->Find(entityID))
			{
				auto* childTransformComponent = child->GetComponent<TransformComponent>();

				childTransformComponent->PreviousPos = childTransformComponent->CurrentPos;
				childTransformComponent->CurrentPos = transformComponent->CurrentPos;
			}
		}
	}
}

void MovementSystem::ApplyKnockback(Entity* entity)
{
	if (!IsKnockbacked(entity))
		return;

	auto* knockbackComponent = entity->GetComponent<KnockbackComponent>();
	auto* velocityComponent = entity->GetComponent<VelocityComponent>();

	velocityComponent->Velocity = knockbackComponent->Direction;
	velocityComponent->Speed = knockbackComponent->Power;					// TOOD: fix side effect where movement speed is increased after knockback
}