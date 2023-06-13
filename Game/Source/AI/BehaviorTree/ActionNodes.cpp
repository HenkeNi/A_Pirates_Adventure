#include "Pch.h"
#include "ActionNodes.h"
#include "../../GameObject/GameObject.h"
#include "../../GameObject/Components/Core/Transform/C_Transform.h"
#include "../../GameObject/Components/Physics/Movement/C_Movement.h"


MoveToTarget::MoveToTarget(GameObject* aTarget)
	: m_target{ aTarget }
{
}

eBTNodeStatus MoveToTarget::Execute(GameObject* anOwner)
{
	if (m_target && anOwner)
	{
		auto targetPosition = m_target->GetComponent<C_Transform>()->GetPosition();
		auto ownerPosition = anOwner->GetComponent<C_Transform>()->GetPosition();	// use ENemy/NPC controller instead??
		
		CU::Vector3<float> direction = targetPosition - ownerPosition;
		direction.y = 0.f;

		if (direction.Length() != 0.f)
			direction.Normalize();

		anOwner->GetComponent<C_Movement>()->SetVelocity(direction);
	}

	return eBTNodeStatus::Running;
}

void MoveToTarget::Clear()
{

}

void MoveToTarget::SetCallback(const std::function<void()>& aCallback)
{
	m_callback = aCallback;
}

void MoveToTarget::SetTarget(GameObject* aTarget)
{
	m_target = aTarget;
}






AttackTarget::AttackTarget(GameObject* aTarget)
	: m_target{ aTarget }
{
}

eBTNodeStatus AttackTarget::Execute(GameObject* anOwner)
{
	std::cout << "Attaclomg..\n";


	anOwner->GetComponent<C_Movement>()->SetVelocity({ 0.f, 0.f, 0.f });

	return eBTNodeStatus::Running;
}

void AttackTarget::Clear()
{

}

void AttackTarget::SetTarget(GameObject* aTarget)
{
	m_target = aTarget;
}







Idle::Idle()
{
}

eBTNodeStatus Idle::Execute(GameObject* anOwner)
{
	return eBTNodeStatus::Invalid;
}

void Idle::Clear()
{
}