#include "Pch.h"
#include "EntityBlueprint.h"



EntityBlueprint::EntityBlueprint()
{
}

EntityBlueprint::~EntityBlueprint()
{
}

void EntityBlueprint::SetIdentifier(const std::string& anIdentifier)
{
	m_identifier = anIdentifier;
}

void EntityBlueprint::AddComponentData(const std::string& aType, const ECS::ComponentData& someData)
{
	if (m_componentData.find(aType) == m_componentData.end())
		m_componentData.insert_or_assign(aType, someData);
}