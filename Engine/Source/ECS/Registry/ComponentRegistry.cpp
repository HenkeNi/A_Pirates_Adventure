#include "Pch.h"
#include "ComponentRegistry.h"

namespace Hi_Engine
{
	bool ComponentRegistry::IsRegistered(ComponentID id) const
	{
		return m_idToComponentData.contains(id);
	}

	const ComponentRegistryEntry& ComponentRegistry::GetComponentRegistryEntry(ComponentID id) const
	{
		assert(m_idToComponentData.contains(id) && "Id not found");
		return m_idToComponentData.at(id);
	}

	const ComponentRegistryEntry& ComponentRegistry::GetComponentRegistryEntry(const char* name) const
	{
		assert(m_nameToComponentData.contains(name) && "Failed!!!!");
		return *m_nameToComponentData.at(name);
	}


	void ComponentRegistry::Clear()
	{
		m_idToComponentData.clear();
		m_nameToComponentData.clear();
		m_typeToComponentData.clear();
	}

	//ComponentID ComponentRegistry::GenerateID() const noexcept
	//{
	//	static ComponentID id = 0;
	//	return id++;
	//}
}
