#include "Pch.h"
#include "ServiceNodes.h"
#include "Entities/Entity.h"
#include "Components/Components.h"


eBTNodeStatus SetWanderPosition::Execute(Entity* entity)
{
	return eBTNodeStatus();
}


eBTNodeStatus SetTargetNode::Execute(Entity* entity)
{
	auto* blackboardComponent = entity->GetComponent<BlackboardComponent>();

	//if (blackboardComponent->IsMovingToPOI)
	//	return eBTNodeStatus::Failure;

	//std::cout << "IDle\n";



	auto* transformComponent = entity->GetComponent<TransformComponent>();
	auto currentPosition = transformComponent->CurrentPos;

	auto* attributesComponent = entity->GetComponent<AttributesComponent>();
	int perception = attributesComponent->Perception;

	auto random = Hi_Engine::GenerateRandomFloatingPointInRadius<float>(currentPosition, perception * Tile::Size);

	blackboardComponent->PointOfInterest = random.GetNormalized() * (perception * Tile::Size);
	blackboardComponent->IsMovingToPOI = true;

	//entity->AddComponent() -> add DestinationComponent instead?
	return eBTNodeStatus();
}

