#include "Pch.h"
#include "ConditionNodes.h"
#include "Components/Components.h"
#include "ECS.h"


eBTNodeStatus IsIdleNode::Execute(Entity entity, ECS& ecs)
{
	if (entity)
	{
		if (auto* characterStateComponent = ecs.GetComponent<StateComponent>(entity))
		{
			//return characterStateComponent->IsIdle ? eBTNodeStatus::Success : eBTNodeStatus::Failure;
			return (characterStateComponent->CurrentState == eState::Idle) ? eBTNodeStatus::Success : eBTNodeStatus::Failure;
		}
	}

	return eBTNodeStatus::Failure;
}

eBTNodeStatus IsDestinationSetNode::Execute(Entity entity, ECS& ecs)
{
	if (entity && ecs.HasComponent<DestinationComponent>(entity))
	{
		return eBTNodeStatus::Success;
	}

	return eBTNodeStatus::Failure;
}

eBTNodeStatus IsDestinationReachedNode::Execute(Entity entity, ECS& ecs)
{
	if (entity)
	{
		auto* destinationComponent = ecs.GetComponent<DestinationComponent>(entity);
		auto* transformComponent = ecs.GetComponent<TransformComponent>(entity);

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

eBTNodeStatus IsTargetSetNode::Execute(Entity entity, ECS& ecs)
{
	if (entity && ecs.HasComponent<TargetComponent>(entity))
	{
		return eBTNodeStatus::Success;
	}

	return eBTNodeStatus::Failure;
}

eBTNodeStatus IsTargetReachedNode::Execute(Entity entity, ECS& ecs)
{
	if (entity)
	{
		auto* targetComponent = ecs.GetComponent<TargetComponent>(entity);
		auto* transformComponent = ecs.GetComponent<TransformComponent>(entity);

		if (targetComponent && transformComponent)
		{
			if (auto target = targetComponent->Target)
			{
				auto* targetTransformComponent = ecs.GetComponent<TransformComponent>(target);

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

eBTNodeStatus IsTargetInSightNode::Execute(Entity entity, ECS& ecs)
{
	// send event request target? passes itself and target component....
	if (entity)
	{
		auto* targetComponent = ecs.GetComponent<TargetComponent>(entity);
		auto* transformComponent = ecs.GetComponent<TransformComponent>(entity);

		if (targetComponent && transformComponent)
		{
			if (auto target = targetComponent->Target)
			{
				auto* targetTransformComponent = ecs.GetComponent<TransformComponent>(target);

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
