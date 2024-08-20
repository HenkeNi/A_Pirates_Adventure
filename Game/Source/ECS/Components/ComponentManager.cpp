#include "Pch.h"
#include "ComponentManager.h"


ComponentManager::ComponentManager()
	: m_nextComponentType{ 1 }
{
}

void ComponentManager::RemoveAllComponents(Entity entity)
{
	for (auto& [type, componentArray] : m_componentArrays)
	{
		componentArray->RemoveComponent(entity);
		/*if (void* removed = componentArray->RemoveComponent(entity))
		{
			auto itr = m_componentPools.find(type);
			if (itr != m_componentPools.end())
			{
				itr->second->ReturnResource(removed);
			}
		}*/
	}
}