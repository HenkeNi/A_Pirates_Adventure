#include "Pch.h"
#include "PhysicsSystem.h"

namespace Hi_Engine
{
    eUpdatePhase PhysicsSystem::GetUpdatePhase() const
    {
        return eUpdatePhase::Update;
    }
}
