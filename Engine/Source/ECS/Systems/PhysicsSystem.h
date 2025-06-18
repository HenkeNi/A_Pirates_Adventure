#pragma once
#include "System.h"

namespace Hi_Engine
{
	class PhysicsSystem : public System
	{
	public:

		eUpdatePhase GetUpdatePhase() const override;
	};
}
