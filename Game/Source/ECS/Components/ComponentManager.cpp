#include "Pch.h"
#include "ComponentManager.h"


ComponentManager::ComponentManager()
	: m_nextComponentType{ 1 }
{
}

//void ComponentManager::AddComponent(Entity entity, std::string name)
//{
//	assert(m_componentRegistry.contains(name) && "[ComponentManager - ERROR]: Couldn't find component type!");
//
//	auto itr = m_componentRegistry.find(name);
//	if (itr != m_componentRegistry.end())
//	{
//		itr->second(entity);
//	}
//}

//void ComponentManager::InitializeComponent(std::string type, void* component, const ComponentProperties& properties)
//{
//	m_componentInitializers[type](component, properties);
//}
