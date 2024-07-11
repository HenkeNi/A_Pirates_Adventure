#include "Pch.h"
#include "EntityFactory.h"


EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}
	
void EntityFactory::LoadBlueprints(const std::string& path)
{
	auto document = Hi_Engine::ParseDocument(path);

	for (auto& blueprintPath : document["blueprints"].GetArray())
	{	
		auto document = Hi_Engine::ParseDocument(blueprintPath.GetString());

		if (document.IsArray())
		{
			for (const auto& blueprint : document.GetArray())
			{
				ConstructBlueprint(blueprint);
			}
		}
		else if (document.IsObject())
		{
			ConstructBlueprint(document);
		}
	}
}

void EntityFactory::ConstructBlueprint(const rapidjson::Value& value)
{
	EntityBlueprint blueprint;

	for (auto& component : value["components"].GetArray())
	{
		const rapidjson::Value& properties = component["properties"];
		assert(properties.IsObject() && "Failed to load component properties for blueprint");

		blueprint.AddComponentData(component["type"].GetString(), ParseComponent(properties));
	}

	std::string blueprintID = value["id"].GetString();
	RegisterBlueprint(blueprintID, blueprint);
}

Entity EntityFactory::Create(const EntityType& type)
{
	auto found = m_blueprints.find(type);

	assert(found != m_blueprints.end() && "ERROR: Failed to create entity - Couldn't find blueprint!");
	Entity entity;

	for (const auto& [type, data] : found->second.m_componentData)
	{
		auto* component = m_componentFactory.Build(type, data);
		entity.AddComponent(component);
	}

	return entity;
}

Entity EntityFactory::CreateFromBlueprint(const EntityBlueprint& blueprint)
{
	Entity entity;
	
	for (const auto& [type, data] : blueprint.m_componentData)
	{
		auto* component = m_componentFactory.Build(type, data);
		entity.AddComponent(component);
	}

	return entity;
}

void EntityFactory::RegisterBlueprint(const std::string& id, EntityBlueprint blueprint)
{
	m_blueprints.insert_or_assign(id, std::move(blueprint)); // no need to move?
}

ComponentData EntityFactory::ParseComponent(const rapidjson::Value& value)
{
	assert(value.IsObject() && "ERROR: Parsing Component");
	ComponentData data;

	for (auto& property : value.GetObject())
	{
		const std::string key = property.name.GetString();
		data.insert_or_assign(key, Hi_Engine::ParseJson(property.value));
	}

	return data;
}