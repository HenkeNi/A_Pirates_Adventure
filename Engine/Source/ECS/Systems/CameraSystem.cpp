#include "Pch.h"
#include "CameraSystem.h"

namespace Hi_Engine
{
	CameraSystem::CameraSystem(World& world)
		: System{ world, eUpdatePhase::Update }
	{
	}

	void CameraSystem::Update(float deltaTime)
	{
	}
}