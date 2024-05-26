#include "Pch.h"
#include "ServiceNodes.h"
#include "Entities/Entity.h"
#include "Components/Components.h"


eBTNodeStatus SetWanderPosition::Execute(Entity* entity)
{
	if (entity)
	{
		if (!entity->HasComponent<DestinationComponent>())
		{
			auto* component = Hi_Engine::MemoryPool<DestinationComponent>::GetInstance().GetResource();
			entity->AddComponent(component);
		}

		auto* transformComponent = entity->GetComponent<TransformComponent>();
		auto currentPosition = transformComponent->CurrentPos;

		auto* attributesComponent = entity->GetComponent<AttributesComponent>();
		int perception = attributesComponent->Perception;

		auto random = Hi_Engine::GenerateRandomFloatingPointInRadius<float>(currentPosition, perception * Tile::Size);

		auto* destinationComponent = entity->GetComponent<DestinationComponent>();
		destinationComponent->Destination = random;
	}

	return eBTNodeStatus::Success;
}


eBTNodeStatus SetTargetNode::Execute(Entity* entity)
{
	if (entity)
	{
		if (!entity->HasComponent<TargetComponent>())
		{
			auto* component = Hi_Engine::MemoryPool<TargetComponent>::GetInstance().GetResource();
			entity->AddComponent(component);
		}

		auto* targetComponent = entity->GetComponent<TargetComponent>();
		auto* blackboardComponent = entity->GetComponent<BlackboardComponent>();

		std::vector<Entity*> targets;

		if (entity->HasComponent<FriendlyComponent>())
		{
			targets = blackboardComponent->Hostile;
			//auto targets = BlackboardComponent::Hostile;
		}
		else if (entity->HasComponent<HostileComponent>())
		{
			targets = blackboardComponent->Friendly;
		}

		// get closes enemy... make function somewhhere

		if (!targets.empty())
		{
			
			auto* transformComponent = entity->GetComponent<TransformComponent>();

			std::sort(targets.begin(), targets.end(), [&](const Entity* lhs, const Entity* rhs) 
			{
					auto* lhsTransformComponent = lhs->GetComponent<TransformComponent>();
					auto* rhsTransformComponent = rhs->GetComponent<TransformComponent>();

					auto lhsDistance = transformComponent->CurrentPos.DistanceTo(lhsTransformComponent->CurrentPos);
					auto rhsDistance = transformComponent->CurrentPos.DistanceTo(rhsTransformComponent->CurrentPos);

					return lhsDistance < rhsDistance;
			});

			targetComponent->Target = targets[0];
		}
		else
		{
			targetComponent->Target = nullptr; // or removee component?
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

