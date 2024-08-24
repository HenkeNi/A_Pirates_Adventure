#include "Pch.h"
#include "PauseCommand.h"


PauseCommand::PauseCommand(ECS& ecs)
	: Command{ ecs }
{
}

void PauseCommand::Execute(Entity entity)
{
	//PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, eScene::Pause });
}

bool PauseCommand::CanPerform(Entity entity) const
{
	return false;
}

