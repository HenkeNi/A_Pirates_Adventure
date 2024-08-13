#include "Pch.h"
#include "PhysicsSystem.h"
#include "ECS.h"
// #include <../Core/Physics/PhysicsEngine.h>


PhysicsSystem::PhysicsSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityCreated, this);
}

PhysicsSystem::~PhysicsSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityCreated, this);
}

void PhysicsSystem::Receive(Message& message)
{
	auto entity = std::any_cast<Entity>(message.GetData());

	if (auto* colliderComponent = m_ecs->GetComponent<ColliderComponent>(entity))
	{
		auto physics = Hi_Engine::ServiceLocator::GetPhysics().lock();

		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);

		switch (colliderComponent->Type)
		{
		case eColliderType::Dynamic:
			colliderComponent->PhysicsBody = physics->CreateDynamicBody({ transformComponent->CurrentPos, transformComponent->Scale, 1.f, 0.3f });
			break;
		case eColliderType::Static:
			// colliderComponent->PhysicsBody = physics->CreateStaticBody({ transformComponent->CurrentPos, transformComponent->Scale });
			break;
		}
	}
}

void PhysicsSystem::LateUpdate(float deltaTime)
{
	ApplyVelocities();

	auto physics = Hi_Engine::ServiceLocator::GetPhysics().lock();
	physics->Update(deltaTime);

	UpdatePositions();
}

void PhysicsSystem::SetSignature()
{
	m_signatures.insert({ "Dynamic", m_ecs->GetSignature<ColliderComponent, VelocityComponent>() }); // replace with physicsComp...
}

void PhysicsSystem::ApplyVelocities()
{
	auto entities = m_ecs->FindEntities(m_signatures["Dynamic"]);

	for (auto entity : entities)
	{
		auto* colliderComponent = m_ecs->GetComponent<ColliderComponent>(entity);

		// FIX!
		if (colliderComponent->Type != eColliderType::Dynamic)
			continue;
		
		auto* velocityComponent = m_ecs->GetComponent<VelocityComponent>(entity);
		colliderComponent->PhysicsBody.SetVelocity(velocityComponent->Velocity);

		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);
		std::cout << transformComponent->CurrentPos.x << ", " << transformComponent->CurrentPos.y << "\n";

	}
}

void PhysicsSystem::UpdatePositions()
{
	auto entities = m_ecs->FindEntities(m_signatures["Dynamic"]);
	
	for (auto entity : entities)
	{
		auto* colliderComponent = m_ecs->GetComponent<ColliderComponent>(entity);

		// FIX!
		if (colliderComponent->Type != eColliderType::Dynamic)
			continue;

		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);

		transformComponent->PreviousPos = transformComponent->CurrentPos; // Needed???
		transformComponent->CurrentPos = colliderComponent->PhysicsBody.GetPosition();
	}
}
