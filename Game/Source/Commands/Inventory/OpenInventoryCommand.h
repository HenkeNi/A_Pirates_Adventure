#pragma once
#include "../Base/Command.h"


class OpenInventoryCommand : public Command
{
public:
	OpenInventoryCommand();

	void Execute(Entity entity)		  override;
	bool CanPerform(Entity entity) const override;

private:

};