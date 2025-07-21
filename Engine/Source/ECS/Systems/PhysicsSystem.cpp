#include "Pch.h"
#include "PhysicsSystem.h"

namespace Hi_Engine
{
    PhysicsSystem::PhysicsSystem(World& world, std::weak_ptr<PhysicsService> physicsService)
        : System{ world, eUpdatePhase::Update }, m_physicsService{ physicsService }
    {
    }
}
