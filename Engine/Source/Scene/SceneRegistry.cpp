#include "Pch.h"
#include "SceneRegistry.h"

namespace Hi_Engine
{
	const SceneRegistryEntry& SceneRegistry::GetEntry(SceneID id) const
	{
		return m_entries.at(id);
	}

	const SceneRegistryEntry& SceneRegistry::GetEntry(const std::string& name) const
	{
		return m_entries.at(m_nameToEntry.at(name)->ID);
	}
}