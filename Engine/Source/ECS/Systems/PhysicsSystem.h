#pragma once
#include "System.h"

namespace Hi_Engine
{
	class PhysicsService;

	class PhysicsSystem : public System
	{
	public:
		PhysicsSystem(World& world, std::weak_ptr<PhysicsService> physicsService);

	private:
		std::weak_ptr<PhysicsService> m_physicsService;
	};
}
