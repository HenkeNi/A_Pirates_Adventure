#include "Pch.h"
#include "OpenInventoryCommand.h"

OpenInventoryCommand::OpenInventoryCommand()
{
}

void OpenInventoryCommand::Execute(Entity* anEntity)
{
	// Send event, should transition..
}

bool OpenInventoryCommand::CanPerform(Entity* anEntity) const
{
	return true;
}
