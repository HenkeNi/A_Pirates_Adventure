#include "Pch.h"
#include "ComponentManager.h"

namespace Hi_Engine
{
	ComponentManager::ComponentManager()
		: m_nextComponentType{ 1 }
	{
	}

	ComponentManager::~ComponentManager()
	{
	}

	void ComponentManager::RemoveAllComponents(Entity entity)
	{
		for (auto& [type, componentArray] : m_componentArrays)
		{
			componentArray->RemoveComponent(entity);
		}
	}
}