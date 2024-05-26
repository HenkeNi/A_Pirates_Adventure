#pragma once

namespace Hi_Engine
{
    class Module
    {
    public:
        virtual ~Module() = default;

       // virtual void Init() = 0;
        virtual void Shutdown() {};
    };
}