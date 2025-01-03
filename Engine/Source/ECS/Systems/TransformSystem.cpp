#include "Pch.h"
#include "TransformSystem.h"

namespace Hi_Engine
{
	void TransformSystem::Update(float deltaTime)
	{
		UpdateSubEntities();
		UpdateOrientation();
	}

	void TransformSystem::UpdateSubEntities()
	{
	}

	void TransformSystem::UpdateOrientation()
	{
	}
}