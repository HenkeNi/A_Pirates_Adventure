#include "Pch.h"
#include "SystemRegistry.h"

namespace Hi_Engine
{
    const std::function<std::unique_ptr<System>()>& SystemRegistry::GetCreator(const char* type) const
    {
        const auto& entry = m_entries.at(type);

        return entry.CreatorFunction;
    }

    bool SystemRegistry::IsRegistered(const char* type) const
    {
        return false;
    }

    SystemID SystemRegistry::GenerateID() const noexcept
    {
        static SystemID id = 0; 
        return id++;
    }
}