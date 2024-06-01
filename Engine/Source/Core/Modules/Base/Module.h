#pragma once
#include <../../../ThirdParty/rapidjson/document.h> //FIX! dont include later...
namespace Hi_Engine
{
    class Module
    {
    public:
        virtual ~Module() = default;

        virtual bool Init() = 0;
        virtual void Shutdown() {};
       
        virtual void Deserialize(const rapidjson::Value& json) {};
        virtual void Serialize() {};
    };
}