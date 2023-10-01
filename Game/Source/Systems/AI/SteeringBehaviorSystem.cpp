#include "Pch.h"
#include "SteeringBehaviorSystem.h"
#include "EntityManager.h"



#include "../AI/SteeringBehaviors/Flock/FlockBehavior.h"

SteeringBehaviorSystem::SteeringBehaviorSystem()
{
}

SteeringBehaviorSystem::~SteeringBehaviorSystem()
{
}

void SteeringBehaviorSystem::Receive(Message& aMsg)
{
}

void SteeringBehaviorSystem::Update(float aDeltaTime)
{
	UpdateWanderBehavior(aDeltaTime);
	UpdateFlockBehavior(aDeltaTime);
	UpdateSeekBehavior(aDeltaTime);
	UpdateFleeBehavior(aDeltaTime);
}

void SteeringBehaviorSystem::UpdateWanderBehavior(float aDeltaTime)
{
	auto entities = m_entityManager->FindAllWithComponents<WanderBehaviorComponent>();

	for (auto entity : entities)
	{
		auto* behaviorComponent = entity->GetComponent<WanderBehaviorComponent>();
		auto* velocityComponent = entity->GetComponent<VelocityComponent>();

		if (auto* activeBehavior = behaviorComponent->Behavior)
		{
			activeBehavior->Update(aDeltaTime);
			
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

void SteeringBehaviorSystem::UpdateFlockBehavior(float aDeltaTime)
{
	// FInd all with sterringBeha and flock Component
	// updat behavior
	return;
	auto entities = m_entityManager->FindAllWithComponents<FlockBehaviorComponent>();



	// auto entities = m_entityManager->FindAllWithComponents<SteeringBehaviorComponent>();

	std::cout << "Updating stereing components..." << entities.size() << '\n';

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

		auto force = flockBehavior->GetSteeringForce({ 0.f, 0.f, 0.f });
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

void SteeringBehaviorSystem::UpdateSeekBehavior(float aDeltaTime)
{

}

void SteeringBehaviorSystem::UpdateFleeBehavior(float aDeltaTime)
{

}