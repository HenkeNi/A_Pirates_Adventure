#include "Pch.h"
#include "EntityFactory.h"
#include "ECS.h"


EntityFactory::EntityFactory(ECS& ecs)
	: m_ecs{ ecs }
{
}

EntityFactory::~EntityFactory()
{
}
	
void EntityFactory::LoadBlueprint(const std::string& path)
{
	auto document = Hi_Engine::ParseDocument(path);

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

void EntityFactory::ConstructBlueprint(const rapidjson::Value& value)
{
	EntityBlueprint blueprint;
	blueprint.Init(value);

	std::string blueprintID = value["id"].GetString();
	RegisterBlueprint(blueprintID, blueprint);
}

Entity EntityFactory::Create(const char* name)
{
	Entity entity = m_ecs.CreateEmptyEntity();

	auto blueprint = m_blueprints.find(name);

	assert(blueprint != m_blueprints.end() && "Blueprint not found");

	const auto& componentProperties = blueprint->second.GetComponentProperties();
	for (const auto& [component, properties] : componentProperties)
	{
		m_ecs.AddComponent(entity, component.c_str()); // fix string!
		m_ecs.InitializeComponent(entity, component.c_str(), properties);
		//ComponentInitializer::InitializeComponent<T>(void*, properties);
	}

	return entity;
}

Entity EntityFactory::Create(const char* name, const rapidjson::Value& value)
{
	Entity entity = m_ecs.CreateEmptyEntity();

	auto blueprint = m_blueprints.find(name);

	assert(blueprint != m_blueprints.end() && "Blueprint not found");

	
	for (const auto& component : value["components_data"].GetArray())
	{

	}

	return entity;
}

//Entity EntityFactory::CreateFromBlueprint(const EntityBlueprint& blueprint)
//{
//	Entity entity;
//	
//	/*for (const auto& [type, data] : blueprint.m_componentData)
//	{
//		auto* component = m_componentFactory.Build(type, data);
//		entity.AddComponent(component);
//	}*/
//
//	return entity;
//}

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