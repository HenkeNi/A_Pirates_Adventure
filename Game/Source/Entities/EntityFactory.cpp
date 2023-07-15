#include "Pch.h"
#include "EntityFactory.h"
#include "Entity.h"


EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

Entity EntityFactory::Create(const std::string& aType)
{
	auto iterator = m_blueprints.find(aType);

	assert(iterator != m_blueprints.end() && "ERROR: Failed to create entity - Couldn't find blueprint!");

	Entity entity;

	for (const auto& type : iterator->second.m_componentData)
	{
		// auto data = type.second;
		auto component = m_componentFactory.Build(type.first, type.second); // TODO; pass in data in constructor? perfect forwarding?
		
		//auto component = m_componentFactory.Create(type);
		//auto component = m_componentFactory.Create(type, data);
		

		// &component = data; // Convert data to an initializer list?


		entity.AddComponent(component);
	}

	return entity;
}

Entity EntityFactory::CreateFromBlueprint(const EntityBlueprint& aBlueprint)
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

