#include "Pch.h"
#include "EntityBlueprint.h"



EntityBlueprint::EntityBlueprint()
{
}

EntityBlueprint::~EntityBlueprint()
{
}

void EntityBlueprint::AddComponentData(const std::string& aType, const std::any& someData)
{
	m_componentData.insert_or_assign(aType, someData);
}

void EntityBlueprint::AddComponentType(const std::string& aType)
{
	m_componentTypes.push_back(aType);
}