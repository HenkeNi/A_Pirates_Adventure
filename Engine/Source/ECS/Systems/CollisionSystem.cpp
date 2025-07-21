#include "Pch.h"
#include "CollisionSystem.h"

namespace Hi_Engine
{
	CollisionSystem::CollisionSystem(World& world)
		: System{ world, eUpdatePhase::Update }
	{
	}
}