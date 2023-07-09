#include "Pch.h"
#include "SteeringBehaviorSystem.h"

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