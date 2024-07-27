#include "Pch.h"
#include "MovementSystem.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"

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
	assert(m_ecs && "ERROR: EntityManager is nullptr!");

	auto entities = m_ecs->FindEntities(m_signatures["Movement"]);

	for (auto entity : entities)
	{
		auto* velocityComponent = m_ecs->GetComponent<VelocityComponent>(entity);

		if (auto* knockbackComponent = m_ecs->GetComponent<KnockbackComponent>(entity))
		{
			ApplyKnockback(velocityComponent, knockbackComponent);
		}


		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);
		transformComponent->PreviousPos = transformComponent->CurrentPos;

		auto& velocity = velocityComponent->Velocity;
		if (!Hi_Engine::Math::IsNearlyEqual(velocity.x, 0.f) && !Hi_Engine::Math::IsNearlyEqual(velocity.y, 0.f))
			velocityComponent->Velocity.Normalize();

		transformComponent->CurrentPos += velocityComponent->Speed * velocityComponent->Velocity * deltaTime;

		if (!velocityComponent->IsVelocityConstant)
			velocityComponent->Velocity = { 0.f, 0.f, };

		//if (HasMoved(entity))
		if (transformComponent->CurrentPos != transformComponent->PreviousPos)
			MoveSubEntities	(entity);
	}
}

void MovementSystem::SetSignature()
{
	m_signatures.insert({ "Camera", m_ecs->GetSignature<CameraComponent>() });
	m_signatures.insert({ "Movement", m_ecs->GetSignature<TransformComponent, VelocityComponent>() });

}


//bool MovementSystem::HasMoved(const Entity* entity)
//{
//	auto transform = entity->GetComponent<TransformComponent>();
//	return transform->CurrentPos != transform->PreviousPos;
//}

//bool MovementSystem::IsKnockbacked(Entity entity)
//{
//	if (auto* knockbackComponent = entity->GetComponent<KnockbackComponent>())
//	{
//		double currentTime = Hi_Engine::Engine::GetTimer().GetTotalTime();
//		double knockbackEndTime = knockbackComponent->Timestamp + knockbackComponent->Duration;
//
//		return knockbackEndTime > currentTime;
//	}
//
//	return false;
//}

void MovementSystem::MoveSubEntities(Entity entity)
{
	// HERE? or in Transform System?
	if (auto* childComponent = m_ecs->GetComponent<SubEntitiesComponent>(entity)) // Change?
	{
		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity); // pass in?

		for (unsigned entityID : childComponent->IDs)
		{
			auto* childTransformComponent = m_ecs->GetComponent<TransformComponent>(entityID);

			childTransformComponent->PreviousPos = childTransformComponent->CurrentPos;
			childTransformComponent->CurrentPos = transformComponent->CurrentPos;
		}
	}
}

//void MovementSystem::ApplyKnockback(Entity* entity)
//{
//
//}

void MovementSystem::ApplyKnockback(VelocityComponent* velocityComponent, KnockbackComponent* knockbackComponent)
{
	double currentTime = Hi_Engine::Engine::GetTimer().GetTotalTime();
	double knockbackEndTime = knockbackComponent->Timestamp + knockbackComponent->Duration;

	if (knockbackEndTime > currentTime)
		return;
	

	velocityComponent->Velocity = knockbackComponent->Direction;
	velocityComponent->Speed = knockbackComponent->Power;					// TOOD: fix side effect where movement speed is increased after knockback
}
