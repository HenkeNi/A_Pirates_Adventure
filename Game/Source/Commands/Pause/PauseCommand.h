#pragma once
#include "../Base/Command.h"

// Send scene transition event?
class PauseCommand : public Command
{
public:
	void Execute(Entity* entity)			override;
	bool CanPerform(Entity* entity) const override;

};