#include "Pch.h"
#include "ConditionNodes.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Components.h"










eBTNodeStatus HasTaget::Execute(Entity* entity)
{
	if (entity)
	{
		auto* blackboardComponent = entity->GetComponent<BlackboardComponent>();

		if (blackboardComponent->IsMovingToPOI)
			return eBTNodeStatus::Success;
	}

	return eBTNodeStatus::Failure;
}

void HasTaget::OnDestroy()
{
}

eBTNodeStatus IsTargetReached::Execute(Entity* entity)
{
	if (entity)
	{
		auto* transformComponent = entity->GetComponent<TransformComponent>();
		auto* blackboardComponent = entity->GetComponent<BlackboardComponent>();

		if (transformComponent->CurrentPos.DistanceTo(blackboardComponent->PointOfInterest) < 0.1f)
		{
			blackboardComponent->IsMovingToPOI = false;
			return eBTNodeStatus::Success;
		}
	}

	return eBTNodeStatus::Failure;
}

void IsTargetReached::OnDestroy()
{
}






eBTNodeStatus DistanceCheckNode::Execute(Entity* entity)
{
	if (entity)
	{
		auto* transformComponent = entity->GetComponent<TransformComponent>();
	
		//auto targetPosition = target->GetComponent<TransformComponent>()->CurrentPos;

		//float distance = currentPosition.DistanceTo(targetPosition);

		//if (distance <= m_radius)
		{
			return eBTNodeStatus::Success;
		}
	}
	return eBTNodeStatus::Failure;
}

void DistanceCheckNode::OnDestroy()
{
}



//eBTNodeStatus TargetInViewNode::Execute(EntityManager* entityManager)
//{
//}
//
//void TargetInViewNode::Clear()
//{
//}
//
//eBTNodeStatus TargetInRangeNode::Execute(EntityManager* entityManager)
//{
//	if (entityManager)
//	{
//		auto* owner = entityManager->Find(m_ownerID);
//
//		if (auto* target = entityManager->Find(m_targetID))
//		{
//
//			auto currentPosition = owner->GetComponent<TransformComponent>()->CurrentPos;
//			auto targetPosition = target->GetComponent<TransformComponent>()->CurrentPos;
//
//			float distance = currentPosition.DistanceTo(targetPosition);
//
//			if (distance <= m_radius)
//			{
//			//	// set attacking to true => walking to false?
//				return eBTNodeStatus::Success;
//			}
//		}
//	}
//	return eBTNodeStatus::Failure;
//}
//
//void TargetInRangeNode::Clear()
//{
//}

eBTNodeStatus CheckEnemyPresenceNode::Execute(Entity* entity)
{
	if (entity)
	{
		auto* transformComponent = entity->GetComponent<TransformComponent>();
		auto currentPosition = transformComponent->CurrentPos;

		auto* attributesComponent = entity->GetComponent<AttributesComponent>();
		int perception = attributesComponent->Perception;

		auto* blackboardComponent = entity->GetComponent<BlackboardComponent>();
		auto playerPosition = blackboardComponent->PlayerPosition;
		
		if (currentPosition.DistanceTo(playerPosition) <= perception * Tile::Size)
		{
			blackboardComponent->PointOfInterest = playerPosition;
			return eBTNodeStatus::Success;
		}
	}

	return eBTNodeStatus::Failure;
}

void CheckEnemyPresenceNode::OnDestroy()
{
}

