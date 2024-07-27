#pragma once
#include "../Base/Command.h"

// Send scene transition event?
class PauseCommand : public Command
{
public:
	void Execute(Entity entity, ECS& ecs)			override;
	bool CanPerform(Entity entity, ECS& ecs) const override;

};