#include "Pch.h"
#include "ActionNodes.h"
#include "Components/Components.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"





IdleNode::IdleNode(int ownerID)
	: BehaviorTreeNode{ ownerID }
{
}

eBTNodeStatus IdleNode::Execute(EntityManager* entityManager)
{
	if (entityManager)
	{
		auto* owner = entityManager->Find(m_ownerID);

		owner->GetComponent<VelocityComponent>()->Velocity = { 0.f, 0.f };
	}

	return eBTNodeStatus::Invalid;
}

void IdleNode::Clear()
{
}










MoveToTargetNode::MoveToTargetNode(int ownerID, int targetID)
	: BehaviorTreeNode{ ownerID }, m_targetID{ targetID }, m_arriveRange{ 0.2f }
{
}

eBTNodeStatus MoveToTargetNode::Execute(EntityManager* entityManager)
{
	if (IsValidTarget() && entityManager)
	{
		// use Enemy/NPC controllers instead??
		auto target = entityManager->Find(m_targetID);
		auto owner	= entityManager->Find(m_ownerID);

		if (!target || !owner)
			return eBTNodeStatus::Failure; // Return failure??

		// Get wander behavior... or seek... set target... 

		const auto targetPosition	= target->GetComponent<TransformComponent>()->CurrentPos;
		const auto ownerPosition	= owner->GetComponent<TransformComponent>()->CurrentPos; 

		auto direction = targetPosition - ownerPosition;
		direction.y = 0.f;

		// TODO; Check distance to target

		if (direction.Length() != 0.f)
			direction.Normalize();

		auto* velocityComponent = owner->GetComponent<VelocityComponent>();
		velocityComponent->Velocity = direction;
		velocityComponent->Speed = 1.f;
	}

	return eBTNodeStatus::Running;
}

void MoveToTargetNode::Clear()
{

}

void MoveToTargetNode::SetCallback(const std::function<void()>& callback)
{
	m_callback = callback;
}

void MoveToTargetNode::SetTargetID(int targetID)
{
	m_targetID = targetID;
}

bool MoveToTargetNode::IsValidTarget() const
{
	return m_targetID != -1;
}






AttackTargetNode::AttackTargetNode(int ownerID, int targetID)
	: BehaviorTreeNode{ ownerID }, m_targetID{ targetID }
{
}

eBTNodeStatus AttackTargetNode::Execute(EntityManager* entityManager)
{
	//std::cout << "Attaclomg..\n";

	if (!entityManager)
		return eBTNodeStatus::Failure; // CORRECT OT RETURN FAILURE??

	if (auto* owner = entityManager->Find(m_ownerID))
	{
		owner->GetComponent<VelocityComponent>()->Velocity = { 0.f, 0.f };
	}

	// enable attack hitbox 

	return eBTNodeStatus::Running;
}

void AttackTargetNode::Clear()
{

}

void AttackTargetNode::SetTargetID(int targetID)
{
	m_targetID = targetID;
}





