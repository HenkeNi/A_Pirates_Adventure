#include "Pch.h"
#include "PauseCommand.h"


void PauseCommand::Execute(Entity entity, ECS& ecs)
{
	//PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, eScene::Pause });
}

bool PauseCommand::CanPerform(Entity entity, ECS& ecs) const
{
	return false;
}
