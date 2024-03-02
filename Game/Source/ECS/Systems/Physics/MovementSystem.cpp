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
}

void MovementSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<TransformComponent, VelocityComponent>();

	for (auto* entity : entities)
	{
		auto* transformComponent = entity->GetComponent<TransformComponent>();
		auto* velocityComponent = entity->GetComponent<VelocityComponent>();

		transformComponent->PreviousPos = transformComponent->CurrentPos;
		transformComponent->CurrentPos += velocityComponent->Speed * velocityComponent->Velocity * aDeltaTime;

		// TODO; decrease velocity... (maybe not for all? => bullets shouldnt decrease?) decrease property?
		if (velocityComponent->ShouldSlowDown) // TODO: FIX! temp solution
			velocityComponent->Velocity = { 0.f, 0.f, };

		// HERE? or in Transform System?
		if (auto* childComponent = entity->GetComponent<SubEntitiesComponent>())
		{
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
}

bool MovementSystem::HasMoved(const Entity* anEntity)
{
	auto transform = anEntity->GetComponent<TransformComponent>();
	return transform->CurrentPos != transform->PreviousPos;
}