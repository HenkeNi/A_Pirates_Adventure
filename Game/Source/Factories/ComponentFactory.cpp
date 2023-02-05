#include "Pch.h"
#include "ComponentFactory.h"
#include "../GameObject/Components/Component.h"


#include "../GameObject/Components/Transform/C_Transform.h"


ComponentFactory::ComponentFactory()
{
}

ComponentFactory::~ComponentFactory()
{
	for (auto comp : m_components)
		delete comp.second;
}

Component* ComponentFactory::CreateComponent(const std::string& aType)
{
	if (!Contains(aType))
		return nullptr;

	return m_components[aType]->Copy();
}

void ComponentFactory::Init()
{
	// DO HERE?????????
	RegisterComponent("transform", new C_Transform{ nullptr });
}

bool ComponentFactory::RegisterComponent(const std::string& aType, Component* aComponent)
{
	assert(aComponent && "Can't register a nullptr");

	if (!Contains(aType))
	{
		return m_components.insert(std::make_pair(aType, aComponent)).second;
	}
	return false;
}

bool ComponentFactory::Contains(const std::string& aType) const
{
	return m_components.find(aType) != m_components.end();
}
