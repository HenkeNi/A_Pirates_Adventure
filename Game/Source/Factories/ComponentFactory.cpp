#include "Pch.h"
#include "ComponentFactory.h"




Component* ComponentFactory::CreateComponent(const std::string& aType)
{
	//return m_components[aType];
	return nullptr;
}

bool ComponentFactory::RegisterComponent(const std::string& aType, Component* aComponent)
{
	return false;
}

bool ComponentFactory::Contains(const std::string& aType) const
{
	return false;
}
