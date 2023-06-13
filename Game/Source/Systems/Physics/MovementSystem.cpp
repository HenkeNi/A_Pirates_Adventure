#include "Pch.h"
#include "MovementSystem.h"
#include "../Entity/Entity.h"
#include "../Entity/EntityManager.h"

#include "../../Entity/Components/Core/CoreComponents.h"
#include "../../Entity/Components/Physics/PhysicsComponents.h"


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
	auto entities = m_entityManager->FindAllWithComponents<TransformComponent, VelocityComponent>();

	for (auto* entity : entities)
	{
		auto* transform = entity->GetComponent<TransformComponent>();
		auto* velocity = entity->GetComponent<VelocityComponent>();

		transform->m_currentPos += velocity->m_velocity * aDeltaTime;
		velocity->m_velocity += velocity->m_acceleration * aDeltaTime;
	}
}