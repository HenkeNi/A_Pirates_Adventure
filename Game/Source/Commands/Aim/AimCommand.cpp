#include "Pch.h"
#include "AimCommand.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"


AimCommand::AimCommand(ECS& ecs)
	: Command{ ecs }
{
}

void AimCommand::Execute(Entity entity)
{
	if (!CanPerform(entity))
		return;

	if (auto* characterStateComponent = m_ecs.GetComponent<CharacterStateComponent>(entity))
	{
		characterStateComponent->IsAiming = true;
		PostMaster::GetInstance().SendMessage({ eMessage::EntityEnteredAim, entity });
	}

	///std::cout << "AIM!!";
}

void AimCommand::Undo(Entity entity)
{
	//std::cout << "\n\n\n" << "Stop Aiming ###############" << "\n\n\n";

	if (auto* characterStateComponent = m_ecs.GetComponent<CharacterStateComponent>(entity))
	{
		characterStateComponent->IsAiming = false;
		PostMaster::GetInstance().SendMessage({ eMessage::EntityExitedAim, entity });
	}
}

bool AimCommand::CanPerform(Entity entity) const
{
	return true;
}