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
	// TODO: listen to collision resolved event (from collision system) => update subentities?
}

void MovementSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

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
		transformComponent->CurrentPos += velocityComponent->Speed * velocityComponent->Velocity * aDeltaTime;

		// TODO; decrease velocity... (maybe not for all? => bullets shouldnt decrease?) decrease property?
		if (velocityComponent->ShouldSlowDown) // TODO: FIX! temp solution
			velocityComponent->Velocity = { 0.f, 0.f, };

		if (HasMoved(entity))
			MoveSubEntities	(entity);
	}
}

bool MovementSystem::HasMoved(const Entity* anEntity)
{
	auto transform = anEntity->GetComponent<TransformComponent>();
	return transform->CurrentPos != transform->PreviousPos;
}

bool MovementSystem::IsKnockbacked(Entity* anEntity)
{
	if (auto* knockbackComponent = anEntity->GetComponent<KnockbackComponent>())
	{
		double currentTime = Hi_Engine::Engine::GetTimer().GetTotalTime();
		double knockbackEndTime = knockbackComponent->Timestamp + knockbackComponent->Duration;

		return knockbackEndTime > currentTime;
	}

	return false;
}

void MovementSystem::MoveSubEntities(Entity* anEntity)
{
	// HERE? or in Transform System?
	if (auto* childComponent = anEntity->GetComponent<SubEntitiesComponent>())
	{
		auto* transformComponent = anEntity->GetComponent<TransformComponent>();

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

void MovementSystem::ApplyKnockback(Entity* anEntity)
{
	if (!IsKnockbacked(anEntity))
		return;

	auto* knockbackComponent = anEntity->GetComponent<KnockbackComponent>();
	auto* velocityComponent = anEntity->GetComponent<VelocityComponent>();

	velocityComponent->Velocity = knockbackComponent->Direction;
	velocityComponent->Speed = knockbackComponent->Power;					// TOOD: fix side effect where movement speed is increased after knockback
}