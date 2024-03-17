#include "Pch.h"
#include "SteeringBehaviorSystem.h"
#include "Entities/EntityManager.h"

#include "Components/AI/AIComponents.h"

#include "../AI/SteeringBehaviors/Flock/FlockBehavior.h"
#include "../AI/SteeringBehaviors/Wander/WanderBehavior.h"

SteeringBehaviorSystem::SteeringBehaviorSystem()
{
}

SteeringBehaviorSystem::~SteeringBehaviorSystem()
{
}

void SteeringBehaviorSystem::Receive(Message& message)
{
}

void SteeringBehaviorSystem::Update(float deltaTime)
{
	UpdateWanderBehavior(deltaTime);
	UpdateFlockBehavior(deltaTime);
	UpdateSeekBehavior(deltaTime);
	UpdateFleeBehavior(deltaTime);
}

void SteeringBehaviorSystem::UpdateWanderBehavior(float deltaTime)
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<WanderBehaviorComponent>();

	for (auto entity : entities)
	{
		auto* behaviorComponent = entity->GetComponent<WanderBehaviorComponent>();
		auto* velocityComponent = entity->GetComponent<VelocityComponent>();

		if (auto* activeBehavior = behaviorComponent->Behavior)
		{
			activeBehavior->Update(deltaTime);
			
			auto currentVelocity = velocityComponent->Velocity;
			auto steeringForce = activeBehavior->GetSteeringForce(currentVelocity);




			static float maxForce = 30.f; // MaxVelocity in Movmenet??
			static float maxSpeed = 60.f;
			static float mass = 20.f;

			if (steeringForce.Length() > maxForce)
			{
				steeringForce.Normalize();
				steeringForce *= maxForce;
			}

			steeringForce /= mass;

			auto combined = currentVelocity + steeringForce;
			if (combined.Length() > maxSpeed)
			{
				combined.Normalize();
				combined *= maxSpeed;
			}

			//std::cout << "combined: " << combined.x << ", " << combined.y << ", " << combined.z << '\n';
			velocityComponent->Velocity = combined;



			// how to update position? => movement?

			//m_activebehavior->update(transform->m_currposition); // use desired position later..??



		}
	}
}

void SteeringBehaviorSystem::UpdateFlockBehavior(float deltaTime)
{
	// FInd all with sterringBeha and flock Component
	// updat behavior
	return;
	auto entities = m_entityManager->FindAll<FlockBehaviorComponent>();



	// auto entities = m_entityManager->FindAll<SteeringBehaviorComponent>();

	//std::cout << "Updating stereing components..." << entities.size() << '\n';

	for (auto* entity : entities)
	{
		auto steeringBehaviorComponent = entity->GetComponent<SteeringBehaviorComponent>();
		auto layer = steeringBehaviorComponent->Layer;

		// flock id...

		// FIX...
		// if (steeringBehaviorComponent-> )

		auto flockBehavior = static_cast<FlockBehavior*>(steeringBehaviorComponent->ActiveBehavior);
		flockBehavior->SetOwner(entity);
		flockBehavior->SetFlockMembers(entities);
		// flockBehavior->Update(aDeltaTime);

		auto force = flockBehavior->GetSteeringForce({ 0.f, 0.f });
		force.y = 0.f;
		entity->GetComponent<VelocityComponent>()->Velocity = force;
		//for (auto* otherEntity : entities)
		//{
		//	auto* otherSteeringBehaviorComponent = otherEntity->GetComponent<SteeringBehaviorComponent>();

		//	if (otherSteeringBehaviorComponent->m_layer == layer)
		//	{
		//		// Check neigbours
		//		


		//	}
		//}
	}

	//m_activeBehavior->Update(aDeltaTime); // TEST---

	//static float maxForce = 30.f; // MaxVelocity in Movmenet??
	//static float maxSpeed = 60.f;
	//static float mass = 20.f;

	//if (m_activeBehavior && m_movement)
	//{
	//	auto currentVelocity = m_movement->GetVelocity();
	//	//auto steeringForce = m_activeBehavior->GetSteeringForce(currentVelocity);

	//	// TEST
	//	auto position = m_owner->GetComponent<C_Transform>()->GetPosition();
	//	auto steeringForce = m_activeBehavior->GetSteeringForce(position, currentVelocity);
	//	//

	//	// add truncate to vector??
	//	if (steeringForce.Length() > maxForce)
	//	{
	//		steeringForce.Normalize();
	//		steeringForce *= maxForce;
	//	}

	//	steeringForce /= mass;

	//	auto combined = currentVelocity + steeringForce;
	//	if (combined.Length() > maxSpeed)
	//	{
	//		combined.Normalize();
	//		combined *= maxSpeed;
	//	}

	//	//std::cout << "Combined: " << combined.x << ", " << combined.y << ", " << combined.z << '\n';
	//	m_movement->SetVelocity(combined);



	//	// how to update position? => movement?

	//	//m_activeBehavior->Update(transform->m_currPosition); // use desired position later..??
	//}
}

void SteeringBehaviorSystem::UpdateSeekBehavior(float deltaTime)
{

}

void SteeringBehaviorSystem::UpdateFleeBehavior(float deltaTime)
{

}