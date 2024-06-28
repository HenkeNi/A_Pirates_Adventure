#include "Pch.h"
#include "ModuleManager.h"
#include "Base/Module.h"
#include <../ThirdParty/rapidjson/document.h>
#include <../ThirdParty/rapidjson/rapidjson.h>

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
        using KVP = std::pair<std::type_index, std::shared_ptr<Module>>;

        std::vector<KVP> modules{ m_modules.begin(), m_modules.end() };
        std::sort(modules.begin(), modules.end(), [](const KVP& m1, const KVP& m2) 
            { 
                return m1.second->GetInitOrder() < m2.second->GetInitOrder(); 
            });

        for (auto& [type, module] : modules)
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