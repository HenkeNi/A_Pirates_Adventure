#include "Pch.h"
#include "UISystem.h"

namespace Hi_Engine
{
    UISystem::UISystem(World& world)
        : System{ world }
    {
    }

    eUpdatePhase UISystem::GetUpdatePhase() const
    {
        return eUpdatePhase::Update;
    }
}