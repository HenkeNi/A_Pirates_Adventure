#include "Pch.h"
#include "OpenInventoryCommand.h"

OpenInventoryCommand::OpenInventoryCommand()
{
}

void OpenInventoryCommand::Execute(Entity* entity)
{
	// Send event, should transition..
}

bool OpenInventoryCommand::CanPerform(Entity* entity) const
{
	return true;
}
