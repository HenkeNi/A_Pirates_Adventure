#include "Pch.h"
#include "AimCommand.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"


AimCommand::AimCommand()
{
}

void AimCommand::Execute(Entity entity, ECS& ecs)
{
	if (!CanPerform(entity, ecs))
		return;

	if (auto* characterStateComponent = ecs.GetComponent<CharacterStateComponent>(entity))
	{
		characterStateComponent->IsAiming = true;
		PostMaster::GetInstance().SendMessage({ eMessage::EntityEnteredAim, entity });
	}

	///std::cout << "AIM!!";
}

void AimCommand::Undo(Entity entity, ECS& ecs)
{
	//std::cout << "\n\n\n" << "Stop Aiming ###############" << "\n\n\n";

	if (auto* characterStateComponent = ecs.GetComponent<CharacterStateComponent>(entity))
	{
		characterStateComponent->IsAiming = false;
		PostMaster::GetInstance().SendMessage({ eMessage::EntityExitedAim, entity });
	}
}

bool AimCommand::CanPerform(Entity entity, ECS& ecs) const
{
	return true;
}