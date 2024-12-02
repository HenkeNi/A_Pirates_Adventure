#pragma once
#include "Dependencies/rapidjson/document.h"


namespace Hi_Engine
{
    class Module
    {
    public:
        Module(int initOrder);
        virtual ~Module() = default;

        virtual bool Init() = 0;
        virtual void Shutdown() {};
        
        virtual void Deserialize(const rapidjson::Value& json) {};
        virtual void Serialize() {};

        inline int   GetInitOrder() const { return m_initOrder; }

    protected:
        int m_initOrder;
    };
}