#include "Pch.h"
#include "PauseCommand.h"


void PauseCommand::Execute(Entity* anEntity)
{
	//	PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, eScene::Pause });
}

bool PauseCommand::CanPerform(Entity* anEntity) const
{
	return false;
}
