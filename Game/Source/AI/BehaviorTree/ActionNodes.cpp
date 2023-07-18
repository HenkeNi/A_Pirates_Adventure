#include "Pch.h"
#include "ActionNodes.h"
#include "Components.h"
#include "Entity.h"
#include "EntityManager.h"


MoveToTarget::MoveToTarget(int anOwnerID, int aTargetID)
	: BehaviorTreeNode{ anOwnerID }, m_targetID{ aTargetID }, m_arriveRange{ 0.2f }
{
}

eBTNodeStatus MoveToTarget::Execute(EntityManager* anEntityManager)
{
	if (IsValidTarget() && anEntityManager)
	{
		// use Enemy/NPC controllers instead??
		auto target = anEntityManager->Find(m_targetID);
		auto owner	= anEntityManager->Find(m_ownerID);

		if (!target || !owner)
			return eBTNodeStatus::Failure; // Return failure??

		const auto targetPosition	= target->GetComponent<TransformComponent>()->m_currentPos;
		const auto ownerPosition	= owner->GetComponent<TransformComponent>()->m_currentPos;

		auto direction = targetPosition - ownerPosition;
		direction.y = 0.f;

		// TODO; Check distance to target

		if (direction.Length() != 0.f)
			direction.Normalize();

		owner->GetComponent<VelocityComponent>()->m_velocity = direction;
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

void MoveToTarget::SetTargetID(int aTargetID)
{
	m_targetID = aTargetID;
}

bool MoveToTarget::IsValidTarget() const
{
	return m_targetID != -1;
}



AttackTarget::AttackTarget(int anOwnerID, int aTargetID)
	: BehaviorTreeNode{ anOwnerID }, m_targetID{ aTargetID }
{
}

eBTNodeStatus AttackTarget::Execute(EntityManager* anEntityManager)
{
	std::cout << "Attaclomg..\n";

	if (!anEntityManager)
		return eBTNodeStatus::Failure; // CORRECT OT RETURN FAILURE??

	if (auto* owner = anEntityManager->Find(m_ownerID))
	{
		owner->GetComponent<VelocityComponent>()->m_velocity = { 0.f, 0.f, 0.f };
	}

	// enable attack hitbox 

	return eBTNodeStatus::Running;
}

void AttackTarget::Clear()
{

}

void AttackTarget::SetTargetID(int aTargetID)
{
	m_targetID = aTargetID;
}







Idle::Idle(int anOwnerID)
	: BehaviorTreeNode{ anOwnerID }
{
}

eBTNodeStatus Idle::Execute(EntityManager* anEntityManager)
{
	if (anEntityManager)
	{
		auto* owner = anEntityManager->Find(m_ownerID);

		owner->GetComponent<VelocityComponent>()->m_velocity = { 0.f, 0.f, 0.f };
	}

	return eBTNodeStatus::Invalid;
}

void Idle::Clear()
{
}