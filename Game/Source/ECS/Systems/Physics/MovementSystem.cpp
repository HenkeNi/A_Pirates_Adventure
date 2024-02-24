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
		auto* transform = entity->GetComponent<TransformComponent>();
		auto* velocity = entity->GetComponent<VelocityComponent>();

		transform->PreviousPos = transform->CurrentPos;
		transform->CurrentPos += velocity->Speed * velocity->Velocity * aDeltaTime;

		// TODO; decrease velocity... (maybe not for all? => bullets shouldnt decrease?) decrease property?
		if (velocity->ShouldSlowDown) // TODO: FIX! temp solution
			velocity->Velocity = { 0.f, 0.f, };
	}
}

bool MovementSystem::HasMoved(const Entity* anEntity)
{
	auto transform = anEntity->GetComponent<TransformComponent>();
	return transform->CurrentPos != transform->PreviousPos;
}