#include "Pch.h"
#include "AimCommand.h"
#include "Entities/Entity.h"
#include "Components/Gameplay/GameplayComponents.h"


AimCommand::AimCommand()
{
}

void AimCommand::Execute(Entity entity)
{
	if (!CanPerform(entity))
		return;

	/*if (auto* characterStateComponent = entity->GetComponent<CharacterStateComponent>())
	{
		characterStateComponent->IsAiming = true;
	}*/

	///std::cout << "AIM!!";
}

void AimCommand::Undo(Entity entity)
{
	//std::cout << "\n\n\n" << "Stop Aiming ###############" << "\n\n\n";

	/*if (auto* characterStateComponent = entity->GetComponent<CharacterStateComponent>())
	{
		characterStateComponent->IsAiming = false;
	}*/

}

bool AimCommand::CanPerform(Entity entity) const
{
	return true;
}