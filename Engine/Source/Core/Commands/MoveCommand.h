#pragma once
#include "Command.h"

namespace Hi_Engine
{
	class MoveCommand : public Command 
	{
	public:
		MoveCommand(float aX, float aY);
		
	};
}