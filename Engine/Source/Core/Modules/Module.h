#pragma once
#include "Dependencies/rapidjson/document.h"


namespace Hi_Engine
{
    class ModuleManager;
    class SystemManager;

    class Module
    {
    public:
        Module(ModuleManager& manager);
        virtual ~Module() = default;

        virtual bool Init() = 0;
        virtual void Shutdown() {};
        
        virtual void Deserialize(const rapidjson::Value& json) {};
        virtual void Serialize() {};

    protected:
        ModuleManager& m_moduleManager;
    };
}