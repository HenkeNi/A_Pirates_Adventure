#include "Pch.h"
#include "ActionNodes.h"


MoveToTarget::MoveToTarget(Entity* aTarget)
	: m_target{ aTarget }
{
}

eBTNodeStatus MoveToTarget::Execute(Entity* anOwner)
{
	if (m_target && anOwner)
	{
		//auto targetPosition = m_target->GetComponent<C_Transform>()->GetPosition();
		//auto ownerPosition = anOwner->GetComponent<C_Transform>()->GetPosition();	// use ENemy/NPC controller instead??
		//
		//CU::Vector3<float> direction = targetPosition - ownerPosition;
		//direction.y = 0.f;

		//if (direction.Length() != 0.f)
		//	direction.Normalize();

		//anOwner->GetComponent<C_Movement>()->SetVelocity(direction);
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

void MoveToTarget::SetTarget(Entity* aTarget)
{
	m_target = aTarget;
}






AttackTarget::AttackTarget(Entity* aTarget)
	: m_target{ aTarget }
{
}

eBTNodeStatus AttackTarget::Execute(Entity* anEntity)
{
	std::cout << "Attaclomg..\n";


	// anEntity->GetComponent<C_Movement>()->SetVelocity({ 0.f, 0.f, 0.f });

	return eBTNodeStatus::Running;
}

void AttackTarget::Clear()
{

}

void AttackTarget::SetTarget(Entity* aTarget)
{
	m_target = aTarget;
}







Idle::Idle()
{
}

eBTNodeStatus Idle::Execute(Entity* anEntity)
{
	return eBTNodeStatus::Invalid;
}

void Idle::Clear()
{
}