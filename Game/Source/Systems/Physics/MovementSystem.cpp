#include "Pch.h"
#include "MovementSystem.h"
#include "Entity.h"
#include "EntityManager.h"

#include "Core/CoreComponents.h"
#include "Physics/PhysicsComponents.h"


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

		transform->m_currentPos += velocity->m_velocity * aDeltaTime;
		velocity->m_velocity += velocity->m_acceleration * aDeltaTime;


		std::cout << "Pos: " << transform->m_currentPos.x << ", " << transform->m_currentPos.y << ", " << transform->m_currentPos.z << '\n';
	}

	// TODO; update if AttackColliders, etc...
}