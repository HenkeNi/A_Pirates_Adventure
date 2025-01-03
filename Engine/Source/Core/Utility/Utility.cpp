#include "Pch.h"
#include "Utility.h"

namespace Hi_Engine
{
	Utility::Utility(ModuleManager& manager)
		: Module{ manager }
	{
	}

	bool Utility::Init()
	{
		return true;
	}
}