#include "Pch.h"
#include "ComponentManager.h"
#include "../GameObject/Components/Component.h"


ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
}

void ComponentManager::RegisterComponent(Component* aComponent)
{
	//assert
}

bool ComponentManager::Contains(Component* aComponent) const
{
	auto container = m_components.find(std::type_index(typeid(Component)));

	if (container != m_components.end())
		return std::find(container->second.begin(), container->second.end(), aComponent) != container->second.end();

	return false;
}