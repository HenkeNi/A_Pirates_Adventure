#include "Pch.h"
#include "EntityFactory.h"
#include "Entity.h"

#include "ComponentParser.h"

#include "Rendering/RenderComponents.h"
#include "Core/CoreComponents.h"
#include "Controllers/ControllerComponents.h"
#include "Physics/PhysicsComponents.h"
#include "Combat/CombatComponents.h"
#include <Stats/StatsComponents.h>
#include "Resource/ResourceComponents.h"
#include "Inventory/InventoryComponents.h"

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

void EntityFactory::LoadBlueprints(const std::string& aFilePath)
{
	auto loadBlueprintsFromJson = [this](const std::string& aFilePath)
	{
		std::ifstream ifs{ aFilePath };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		document.Parse(content.c_str());

		assert(!document.HasParseError() && "Failed to parse Blueprints");

		EntityBlueprint blueprint;

		for (auto& component : document["components"].GetArray())
		{
			std::string type = component["type"].GetString(); // noT WOKRIG!!! ALSO EXPAND WITH MORE CASES
			
			auto componentData = ComponentParser::ParseComponentFromJson(type, component);
			blueprint.AddComponent(type, componentData);
		}

		RegisterBlueprint(document["name"].GetString(), blueprint);
	};

	std::ifstream ifs{ aFilePath };
	std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

	rapidjson::Document document;
	document.Parse(content.c_str());

	assert(!document.HasParseError() && "Failed to parse Blueprints");

	for (auto& blueprint : document["blueprints"]["player"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}

	for (auto& blueprint : document["blueprints"]["enemies"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}

	for (auto& blueprint : document["blueprints"]["props"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}

	for (auto& blueprint : document["blueprints"]["cameras"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}

	for (auto& blueprint : document["blueprints"]["resources"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}

	for (auto& blueprint : document["blueprints"]["spawners"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}

	for (auto& blueprint : document["blueprints"]["map"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}
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

