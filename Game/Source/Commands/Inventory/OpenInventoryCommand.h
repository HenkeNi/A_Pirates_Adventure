#pragma once
#include "../Base/Command.h"


class OpenInventoryCommand : public Command
{
public:
	OpenInventoryCommand();

	void Execute(Entity entity, ECS& ecs)		  override;
	bool CanPerform(Entity entity, ECS& ecs) const override;

private:

};