#include "Pch.h"
#include "CameraSystem.h"

namespace Hi_Engine
{
	CameraSystem::CameraSystem(World& world)
		: System{ world }
	{
	}

	void CameraSystem::Update(float deltaTime)
	{
	}

	eUpdatePhase CameraSystem::GetUpdatePhase() const
	{
		return eUpdatePhase::Update;
	}
}