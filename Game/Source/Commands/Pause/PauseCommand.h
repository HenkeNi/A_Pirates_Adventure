#pragma once
#include "../Base/Command.h"

// Send scene transition event?
class PauseCommand : public Command
{
public:
	void Execute(Entity* anEntity)			override;
	bool CanPerform(Entity* anEntity) const override;

};