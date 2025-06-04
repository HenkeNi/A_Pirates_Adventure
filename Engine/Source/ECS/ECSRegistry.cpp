#include "Pch.h"
#include "ECSRegistry.h"
#include "Registry/ComponentRegistry.h"
#include "Registry/SystemRegistry.h"
#include "Factory/ComponentFactory.h"
#include "Factory/EntityFactory.h"

namespace Hi_Engine
{
    std::unique_ptr<EntityFactory> ECSRegistry::s_entityFactory = std::make_unique<EntityFactory>();

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