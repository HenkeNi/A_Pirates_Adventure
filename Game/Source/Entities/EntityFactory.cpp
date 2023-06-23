#include "Pch.h"
#include "EntityFactory.h"
#include "Entity.h"


EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

Entity EntityFactory::Create(const std::string& aType) const
{
	auto it = m_blueprints.find(aType);
	if (it != m_blueprints.end())
	{
		Entity entity;
	
		for (const auto& type : it->second.m_componentTypes)
		{
			auto data = it->second.m_componentData;

			auto component = m_componentFactory.Build(type); // TODO; pass in data in constructor? perfect forwarding?

			entity.AddComponent(component);
			
		

		}

		return entity;
	}

	return Entity{};
}

Entity EntityFactory::CreateFromBlueprint(const EntityBlueprint& aBlueprint) const
{
	return {};
}

void EntityFactory::RegisterBlueprint(const std::string& aType, EntityBlueprint aBlueprint)
{
	m_blueprints.insert_or_assign(aType, std::move(aBlueprint));
}

void EntityFactory::RegisterComponentBuilder(Identifier& aType, ComponentBaseBuilder* aBuilder)
{
	m_componentFactory.RegisterBuilder(aType, aBuilder);
}