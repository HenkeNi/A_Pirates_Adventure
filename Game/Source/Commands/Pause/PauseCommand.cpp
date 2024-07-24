#include "Pch.h"
#include "PauseCommand.h"


void PauseCommand::Execute(Entity entity)
{
	//	PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, eScene::Pause });
}

bool PauseCommand::CanPerform(Entity entity) const
{
	return false;
}
