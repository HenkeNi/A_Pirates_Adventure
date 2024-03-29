#include "Pch.h"
#include "DistanceConditions.h"
#include "Entities/Entity.h"
#include "Components/AI/AIComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"


InRangeCondition::InRangeCondition(float range)
	: m_range{ range }
{
}

void InRangeCondition::Init()
{
}

bool InRangeCondition::IsSatisfied(Entity* entity) const
{
	if (!entity)
		return false;

	if (auto* blackboardComponent = entity->GetComponent<BlackboardComponent>())
	{
		auto* transformComponent = entity->GetComponent<TransformComponent>();
		return transformComponent->CurrentPos.DistanceTo(blackboardComponent->PlayerPosition) <= m_range;
	}

	return false;
}

void HasAttackedCondition::Init()
{
}

bool HasAttackedCondition::IsSatisfied(Entity* entity) const
{
	if (!entity)
		return false;

	if (auto* characterStateComponent = entity->GetComponent<CharacterStateComponent>())
	{
		return characterStateComponent->IsAttacking;
	}

	return false;
}
