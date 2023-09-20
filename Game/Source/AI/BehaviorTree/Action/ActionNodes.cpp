#include "Pch.h"
#include "ActionNodes.h"
#include "Components.h"
#include "Entity.h"
#include "EntityManager.h"





IdleNode::IdleNode(int anOwnerID)
	: BehaviorTreeNode{ anOwnerID }
{
}

eBTNodeStatus IdleNode::Execute(EntityManager* anEntityManager)
{
	if (anEntityManager)
	{
		auto* owner = anEntityManager->Find(m_ownerID);

		owner->GetComponent<VelocityComponent>()->m_velocity = { 0.f, 0.f, 0.f };
	}

	return eBTNodeStatus::Invalid;
}

void IdleNode::Clear()
{
}










MoveToTargetNode::MoveToTargetNode(int anOwnerID, int aTargetID)
	: BehaviorTreeNode{ anOwnerID }, m_targetID{ aTargetID }, m_arriveRange{ 0.2f }
{
}

eBTNodeStatus MoveToTargetNode::Execute(EntityManager* anEntityManager)
{
	if (IsValidTarget() && anEntityManager)
	{
		// use Enemy/NPC controllers instead??
		auto target = anEntityManager->Find(m_targetID);
		auto owner	= anEntityManager->Find(m_ownerID);

		if (!target || !owner)
			return eBTNodeStatus::Failure; // Return failure??

		// Get wander behavior... or seek... set target... 

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

void MoveToTargetNode::Clear()
{

}

void MoveToTargetNode::SetCallback(const std::function<void()>& aCallback)
{
	m_callback = aCallback;
}

void MoveToTargetNode::SetTargetID(int aTargetID)
{
	m_targetID = aTargetID;
}

bool MoveToTargetNode::IsValidTarget() const
{
	return m_targetID != -1;
}






AttackTargetNode::AttackTargetNode(int anOwnerID, int aTargetID)
	: BehaviorTreeNode{ anOwnerID }, m_targetID{ aTargetID }
{
}

eBTNodeStatus AttackTargetNode::Execute(EntityManager* anEntityManager)
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

void AttackTargetNode::Clear()
{

}

void AttackTargetNode::SetTargetID(int aTargetID)
{
	m_targetID = aTargetID;
}





