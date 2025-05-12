#include "Pch.h"
#include "ECSRegistry.h"
#include "Registry/ComponentRegistry.h"
#include "Registry/SystemRegistry.h"

namespace Hi_Engine
{
    ComponentRegistry& ECSRegistry::GetComponentRegistry()
    {
        static ComponentRegistry instance;
        return instance;
    }

    SystemRegistry& ECSRegistry::GetSystemRegistry()
    {
        static SystemRegistry instance;
        return instance;
    }
}