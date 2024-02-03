#include "Pch.h"
#include "AimCommand.h"
#include "Entities/Entity.h"
#include "Components/Gameplay/GameplayComponents.h"


AimCommand::AimCommand()
{
}

void AimCommand::Execute(Entity* anEntity)
{
	if (!CanPerform(anEntity))
		return;

	if (auto* characterStateComponent = anEntity->GetComponent<CharacterStateComponent>())
	{
		characterStateComponent->IsAiming = true;
	}

	///std::cout << "AIM!!";
}

void AimCommand::Undo(Entity* anEntity)
{
	//std::cout << "\n\n\n" << "Stop Aiming ###############" << "\n\n\n";

	if (auto* characterStateComponent = anEntity->GetComponent<CharacterStateComponent>())
	{
		characterStateComponent->IsAiming = false;
	}

}

bool AimCommand::CanPerform(Entity* anEntity) const
{
	return true;
}