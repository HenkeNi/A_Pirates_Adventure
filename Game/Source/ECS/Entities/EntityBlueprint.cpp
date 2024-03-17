#include "Pch.h"
#include "EntityBlueprint.h"



EntityBlueprint::EntityBlueprint()
{
}

EntityBlueprint::~EntityBlueprint()
{
}

void EntityBlueprint::SetIdentifier(const std::string& identifier)
{
	m_identifier = identifier;
}

void EntityBlueprint::AddComponentData(const std::string& type, const ECS::ComponentData& data)
{
	if (m_componentData.find(type) == m_componentData.end())
		m_componentData.insert_or_assign(type, data);
}