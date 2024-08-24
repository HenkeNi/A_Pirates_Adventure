#include "Pch.h"
#include "OpenInventoryCommand.h"
#include "SceneTypes.h"

OpenInventoryCommand::OpenInventoryCommand(ECS& ecs)
	: Command{ ecs }
{
}

void OpenInventoryCommand::Execute(Entity entity)
{
	// Send event, should transition..

	PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, eScene::Inventory }); // Will not call game scenes inventory scene??
}

bool OpenInventoryCommand::CanPerform(Entity entity) const
{
	return true;
}
