#include "Pch.h"
#include "ConditionNodes.h"
#include "Entities/Entity.h"
#include "Components/Components.h"






eBTNodeStatus IsIdleNode::Execute(Entity* entity)
{
	if (entity)
	{
		if (auto* characterStateComponent = entity->GetComponent<CharacterStateComponent>())
		{
			return characterStateComponent->IsIdle ? eBTNodeStatus::Success : eBTNodeStatus::Failure;
		}
	}

	return eBTNodeStatus::Failure;
}

eBTNodeStatus IsDestinationSetNode::Execute(Entity* entity)
{
	if (entity && entity->HasComponent<DestinationComponent>())
	{
		return eBTNodeStatus::Success;
	}

	return eBTNodeStatus::Failure;
}

eBTNodeStatus IsDestinationReachedNode::Execute(Entity* entity)
{
	if (entity)
	{
		auto* destinationComponent = entity->GetComponent<DestinationComponent>();
		auto* transformComponent = entity->GetComponent<TransformComponent>();

		if (destinationComponent && transformComponent)
		{
			const auto& currentPosition = transformComponent->CurrentPos;
			const auto& desiredPosition = destinationComponent->Destination;

			if (currentPosition.DistanceTo(desiredPosition) <= destinationComponent->ArriveRadius)
				return eBTNodeStatus::Success;
		}
	}
	return eBTNodeStatus::Failure;
}

eBTNodeStatus IsTargetSetNode::Execute(Entity* entity)
{
	if (entity && entity->HasComponent<TargetComponent>())
	{
		return eBTNodeStatus::Success;
	}

	return eBTNodeStatus::Failure;
}

eBTNodeStatus IsTargetReachedNode::Execute(Entity* entity)
{
	if (entity)
	{
		auto* targetComponent = entity->GetComponent<TargetComponent>();
		auto* transformComponent = entity->GetComponent<TransformComponent>();

		if (targetComponent && transformComponent)
		{
			if (auto* target = targetComponent->Target)
			{
				auto* targetTransformComponent = target->GetComponent<TransformComponent>();

				const auto& targetPosition = targetTransformComponent->CurrentPos;
				const auto& currentPosition = transformComponent->CurrentPos;

				if (currentPosition.DistanceTo(targetPosition) < 0.1f)
				{
					return eBTNodeStatus::Success;
				}
			}
		}
	}
	return eBTNodeStatus::Failure;
}

eBTNodeStatus IsTargetInSightNode::Execute(class Entity* entity)
{
	// send event request target? passes itself and target component....
	if (entity)
	{
		auto* targetComponent = entity->GetComponent<TargetComponent>();
		auto* transformComponent = entity->GetComponent<TransformComponent>();

		if (targetComponent && transformComponent)
		{
			if (auto* target = targetComponent->Target)
			{
				auto* targetTransformComponent = target->GetComponent<TransformComponent>();

				const auto& targetPosition = targetTransformComponent->CurrentPos;
				const auto& currentPosition = transformComponent->CurrentPos;

				if (currentPosition.DistanceTo(targetPosition) < 2.1f)
				{
					return eBTNodeStatus::Success;
				}
			}
		}
	}

	return eBTNodeStatus::Failure;
}
