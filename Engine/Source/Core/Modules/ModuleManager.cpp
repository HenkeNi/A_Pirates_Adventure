#include "Pch.h"
#include "ModuleManager.h"
#include "Module.h"
//#include <../ThirdParty/rapidjson/document.h>
//#include <../ThirdParty/rapidjson/rapidjson.h>

namespace Hi_Engine
{
    ModuleManager::ModuleManager()
    {
        m_modules.reserve(10);
    }

    ModuleManager::~ModuleManager()
    {
    }

    bool ModuleManager::Init()
    {
        for (auto& [type, module] : m_modules)
        {
            if (!module->Init())
            {
                return false;
            }
        }

        return true;
    }

    void ModuleManager::Shutdown()
    {
        for (auto& [type, module] : m_modules)
        {
            module->Shutdown();
        }
    }

    void ModuleManager::LoadModules()
    {
        auto document = ParseDocument("../Engine/Assets/Json/Settings/Settings.json");
        
        for (auto& [type, module] : m_modules)
        {
            module->Deserialize(document.GetObj());
        }
    }
}