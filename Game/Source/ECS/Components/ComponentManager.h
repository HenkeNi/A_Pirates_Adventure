#pragma once

#include "ComponentArray.h"

using Entity = int;

class IComponentArray;

class ComponentManager
{
public:

	template <typename T>
	void AddComponent(Entity entity);

private:
	// Component factory
	// ComponentArray

	std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> m_componentArrays;
	
	// Hi_Engine::MemoryPool<Component>
	//Hi_Engine::MemoryPool<std::type_index>
};

#pragma region Method_Definitions

template<typename T>
inline void ComponentManager::AddComponent(Entity entity)
{
	T* component = Hi_Engine::MemoryPool<T>::GetInstance().GetResource(); // TODO; store in ComponentManager!
	
	auto type = std::type_index(typeid(T));
	
	assert(m_componentArrays.contains(type) && "ERROR: no such component array found");
	auto iterator = m_componentArrays.find(type);
	
	if (iterator != m_componentArrays.end())
	{
		iterator->second->AddComponent(entity, component);
	}

}

#pragma endregion Method_Definitions