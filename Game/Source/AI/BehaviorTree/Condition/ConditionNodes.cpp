#include "Pch.h"
#include "ConditionNodes.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Components.h"


eBTNodeStatus TargetInViewNode::Execute(EntityManager* entityManager)
{
	if (entityManager)
	{
		auto* owner = entityManager->Find(m_ownerID);
		auto* target = entityManager->Find(m_targetID); // target ID becomes invalid..

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







eBTNodeStatus TargetInRangeNode::Execute(EntityManager* entityManager)
{
	if (entityManager)
	{
		auto* owner = entityManager->Find(m_ownerID);

		if (auto* target = entityManager->Find(m_targetID))
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