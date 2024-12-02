#include "Pch.h"
#include "ServiceNodes.h"
#include "Components/Components.h"
#include "ECS.h"


eBTNodeStatus SetWanderPosition::Execute(Entity entity, ECS& ecs)
{
	if (entity)
	{
		if (!ecs.HasComponent<DestinationComponent>(entity))
		{
			//auto* component = Hi_Engine::MemoryPool<DestinationComponent>::GetInstance().GetResource();
			ecs.AddComponent<DestinationComponent>(entity);
		}

		auto* transformComponent = ecs.GetComponent<TransformComponent>(entity);
		auto currentPosition = transformComponent->CurrentPos;

		auto* attributesComponent = ecs.GetComponent<AttributesComponent>(entity);
		int perception = attributesComponent->Perception;

		auto random = Hi_Engine::GenerateRandomFloatingPointInRadius<float>(currentPosition, perception * Tile::Size);

		auto* destinationComponent = ecs.GetComponent<DestinationComponent>(entity);
		destinationComponent->Destination = random;
	}

	return eBTNodeStatus::Success;
}


eBTNodeStatus SetTargetNode::Execute(Entity entity, ECS& ecs)
{
	if (entity)
	{
		if (!ecs.HasComponent<TargetComponent>(entity))
		{
			// auto* component = Hi_Engine::MemoryPool<TargetComponent>::GetInstance().GetResource();
			ecs.AddComponent<TargetComponent>(entity);
		}

		auto* targetComponent = ecs.GetComponent<TargetComponent>(entity);
		auto* blackboardComponent = ecs.GetComponent<BlackboardComponent>(entity);

		std::vector<Entity> targets;

		//if (ecs.HasComponent<FriendlyComponent>(entity))
		//{
		//	// targets = blackboardComponent->Hostile;
		//	//auto targets = BlackboardComponent::Hostile;
		//}
		//else if (ecs.HasComponent<HostileComponent>(entity))
		//{
		//	// targets = blackboardComponent->Friendly;
		//}

		// get closes enemy... make function somewhhere

		if (!targets.empty())
		{
			
			auto* transformComponent = ecs.GetComponent<TransformComponent>(entity);

			std::sort(targets.begin(), targets.end(), [&](Entity lhs, Entity rhs) 
			{
					auto* lhsTransformComponent = ecs.GetComponent<TransformComponent>(lhs);
					auto* rhsTransformComponent = ecs.GetComponent<TransformComponent>(rhs);

					auto lhsDistance = transformComponent->CurrentPos.DistanceTo(lhsTransformComponent->CurrentPos);
					auto rhsDistance = transformComponent->CurrentPos.DistanceTo(rhsTransformComponent->CurrentPos);

					return lhsDistance < rhsDistance;
			});

			targetComponent->Target = targets[0];
		}
		else
		{
			targetComponent->Target = 0; // or removee component?
		}
	}


	//auto* transformComponent = entity->GetComponent<TransformComponent>();
	//auto currentPosition = transformComponent->CurrentPos;

	//auto* attributesComponent = entity->GetComponent<AttributesComponent>();
	//int perception = attributesComponent->Perception;

	//auto random = Hi_Engine::GenerateRandomFloatingPointInRadius<float>(currentPosition, perception * Tile::Size);

	//blackboardComponent->PointOfInterest = random.GetNormalized() * (perception * Tile::Size);
	//blackboardComponent->IsMovingToPOI = true;

	//entity->AddComponent() -> add DestinationComponent instead?
	return eBTNodeStatus::Success;
}

