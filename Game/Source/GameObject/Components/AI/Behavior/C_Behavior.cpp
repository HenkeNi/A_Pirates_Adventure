#include "Pch.h"
#include "C_Behavior.h"
#include "../GameObject/GameObject.h"
#include "../../../../Gameplay/SteeringBehaviors/WanderBehavior.h"
#include "../../Physics/Movement/C_Movement.h"


C_Behavior::C_Behavior(GameObject* anOwner)
	: Component{ anOwner }
{
	m_activeBehavior = new WanderBehavior;
}

void C_Behavior::Init(rapidjson::Value& aValue)			
{

}

void C_Behavior::HandleMessage(const CompMessage& aMsg)	
{
}

void C_Behavior::Update(float aDeltaTime)				
{
	static float maxForce = 30.f; // MaxVelocity in Movmenet??
	static float maxSpeed = 60.f;
	static float mass = 20.f;

	if (m_activeBehavior)
	{
		auto currentVelocity = m_movement->GetVelocity();
		auto steeringForce = m_activeBehavior->GetSteeringForce(currentVelocity);

		// add truncate to vector??
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

		std::cout << "Combined: " << combined.x << ", " << combined.y << ", " << combined.z << '\n';
		m_movement->SetVelocity(combined);



		// how to update position? => movement?

		//m_activeBehavior->Update(transform->m_currPosition); // use desired position later..??
	}

}

void C_Behavior::LateUpdate(float aDeltaTime)			
{
}

void C_Behavior::OnActivate()							
{
	m_movement = m_owner->GetComponent<C_Movement>();
}

C_Behavior* C_Behavior::Copy() const
{
	auto* res = CU::MemoryPool<C_Behavior>::GetInstance().GetResource();	// TODO; register in ComponentManager?
	assert(res && "Memory Pool returned invalid memory");

	return new (res) C_Behavior{ *this };
}