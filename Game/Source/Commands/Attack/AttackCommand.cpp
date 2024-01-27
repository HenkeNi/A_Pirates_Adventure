#include "Pch.h"
#include "AttackCommand.h"
#include "Entities/Entity.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Components/Core/CoreComponents.h"


AttackCommand::AttackCommand()
{
}

void AttackCommand::Execute(Entity* anEntity)
{
	if (!anEntity)
		return;

	if (auto* characterStateComponent = anEntity->GetComponent<CharacterStateComponent>())
	{
		characterStateComponent->IsAttacking = true;
	}

	if (auto* attackComponent = anEntity->GetComponent<AttackComponent>())
	{
		attackComponent->IsEnabled = true;
	}
}

bool AttackCommand::CanPerform(Entity* anEntity) const
{
	if (anEntity)
	{
		if (auto* characterStateComponent = anEntity->GetComponent<CharacterStateComponent>())
		{
			return !characterStateComponent->IsAttacking;
		}
	}

	return false;
}