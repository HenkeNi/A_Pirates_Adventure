#include "Pch.h"
#include "PhysicsSystem.h"
#include "ECS.h"


PhysicsSystem::PhysicsSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityCreated, this);
	PostMaster::GetInstance().Subscribe(eMessage::EntityDestroyed, this);
}

PhysicsSystem::~PhysicsSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityCreated, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityDestroyed, this);
}

void PhysicsSystem::Receive(Message& message)
{
	assert(m_ecs && "[PhysicsSystem - ERROR]: ECS is not initialized!");

	auto entity = std::any_cast<Entity>(message.GetData());

	if (!m_ecs->HasComponent<PhysicsComponent>(entity))
		return;

	if (message.GetMessageType() == eMessage::EntityCreated)
	{
		AttachPhysicsBody(entity);
	}
	else if (message.GetMessageType() == eMessage::EntityDestroyed)
	{
		RemovePhysicsBody(entity);
	}
}

void PhysicsSystem::LateUpdate(float deltaTime)
{
	assert(m_ecs && "[PhysicsSystem - ERROR]: ECS is not initialized!");

	ApplyVelocities();

	auto physics = Hi_Engine::ServiceLocator::GetPhysics().lock();
	physics->Update(deltaTime);

	UpdatePositions();
}

void PhysicsSystem::SetSignature()
{
	m_signatures.insert({ "Dynamic", m_ecs->GetSignature<PhysicsComponent, VelocityComponent>() }); // replace with physicsComp...
}

void PhysicsSystem::ApplyVelocities()
{
	auto entities = m_ecs->FindEntities(m_signatures["Dynamic"]);

	for (auto entity : entities)
	{
		auto* physicsComponent = m_ecs->GetComponent<PhysicsComponent>(entity);

		assert(physicsComponent->Type == eColliderType::Dynamic && "[PhysicsSystem::ApplyVelocities] - PhysicsBody is not dynamic");

		auto* velocityComponent = m_ecs->GetComponent<VelocityComponent>(entity);
		physicsComponent->PhysicsBody.SetVelocity(velocityComponent->Velocity * 100.f);
		//colliderComponent->PhysicsBody.ApplyForce(velocityComponent->Velocity * 100.f);
	}
}

void PhysicsSystem::UpdatePositions()
{
	auto entities = m_ecs->FindEntities(m_signatures["Dynamic"]);
	
	for (auto entity : entities)
	{
		auto* colliderComponent = m_ecs->GetComponent<PhysicsComponent>(entity);

		// FIX!
		if (colliderComponent->Type != eColliderType::Dynamic)
			continue;

		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);

		transformComponent->PreviousPos = transformComponent->CurrentPos; // Needed???
		transformComponent->CurrentPos = colliderComponent->PhysicsBody.GetPosition();
	}
}

void PhysicsSystem::AttachPhysicsBody(Entity entity)
{
	auto* physicsComponent = m_ecs->GetComponent<PhysicsComponent>(entity);
	auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);

	if (physicsComponent && transformComponent)
	{
		auto physics = Hi_Engine::ServiceLocator::GetPhysics().lock();

		switch (physicsComponent->Type)
		{
		case eColliderType::Dynamic:
			physicsComponent->PhysicsBody = physics->CreateDynamicBody({ transformComponent->CurrentPos, transformComponent->Scale, physicsComponent->Density, physicsComponent->Friction });
			break;
		case eColliderType::Static:
			physicsComponent->PhysicsBody = physics->CreateStaticBody({ transformComponent->CurrentPos, transformComponent->Scale });
			break;
		}
	}
}

void PhysicsSystem::RemovePhysicsBody(Entity entity)
{
	if (auto* physicsComponent = m_ecs->GetComponent<PhysicsComponent>(entity))
	{
		auto physics = Hi_Engine::ServiceLocator::GetPhysics().lock();
		physics->DestroyBody(physicsComponent->PhysicsBody);
	}
}
