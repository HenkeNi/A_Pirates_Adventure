#include "Pch.h"
#include "ModuleManager.h"
#include "Base/Module.h"

namespace Hi_Engine
{
    void ModuleManager::Init()
    {
        for (auto& [type, module] : m_modules) 
        {
           // module->Init();
        }
    }

    void ModuleManager::Shutdown()
    {
        for (auto& [type, module] : m_modules)
        {
          //  module->Shutdown();
        }
    }
}