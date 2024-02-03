#pragma once
#include "../Base/Command.h"

// Or just one attack command?
class ShootCommand : public Command
{
public:
	ShootCommand();

	void Execute();

};