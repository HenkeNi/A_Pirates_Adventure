#include "Pch.h"
#include "ConditionNodes.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Components.h"


TargetInViewNode::TargetInViewNode(int anOwnerID, int aTargetID)
	: BehaviorTreeNode{ anOwnerID }, m_targetID{ aTargetID }, m_radius{ 2.f }
{
}

eBTNodeStatus TargetInViewNode::Execute(EntityManager* anEntityManager)
{
	if (anEntityManager)
	{
		auto* owner = anEntityManager->Find(m_ownerID);
		auto* target = anEntityManager->Find(m_targetID); // target ID becomes invalid..

		auto currentPosition = owner->GetComponent<TransformComponent>()->CurrentPos;
		auto targetPosition = target->GetComponent<TransformComponent>()->CurrentPos;

		float distance = currentPosition.DistanceTo(targetPosition);

		if (distance <= m_radius)
		{
			return eBTNodeStatus::Success;
		}
	}
	return eBTNodeStatus::Failure;
}

void TargetInViewNode::Clear()
{

}







TargetInRangeNode::TargetInRangeNode(int anOwnerID, int aTargetID)
	: BehaviorTreeNode{ anOwnerID }, m_targetID{ aTargetID }, m_radius{ 0.5f }
{
}

eBTNodeStatus TargetInRangeNode::Execute(EntityManager* anEntityManager)
{
	if (anEntityManager)
	{
		auto* owner = anEntityManager->Find(m_ownerID);

		if (auto* target = anEntityManager->Find(m_targetID))
		{

			auto currentPosition = owner->GetComponent<TransformComponent>()->CurrentPos;
			auto targetPosition = target->GetComponent<TransformComponent>()->CurrentPos;

			float distance = currentPosition.DistanceTo(targetPosition);

			if (distance <= m_radius)
			{
			//	// set attacking to true => walking to false?
				return eBTNodeStatus::Success;
			}
		}
	}
	return eBTNodeStatus::Failure;
}

void TargetInRangeNode::Clear()
{

}