#include "Pch.h"
#include "EntityFactory.h"
#include "ECS.h"
// #include "ECSTypes.h"


EntityFactory::EntityFactory(EntityManager& entityManager, ComponentRegistry& componentRegistry)
	: m_entityManager{ entityManager }, m_componentRegistry{ componentRegistry }
{
}

EntityFactory::~EntityFactory()
{
}

void EntityFactory::LoadBlueprints()
{
	const char* path = "../Game/Assets/Json/Blueprints/blueprint_manifest.json";

	auto document = Hi_Engine::ParseDocument(path);

	for (auto& path : document["blueprints"].GetArray())
	{
		std::string blueprintPath = path.GetString();

		auto document = Hi_Engine::ParseDocument(blueprintPath);

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
	
//void EntityFactory::LoadBlueprint(const std::string& path)
//{
//	auto document = Hi_Engine::ParseDocument(path);
//
//	if (document.IsArray())
//	{
//		for (const auto& blueprint : document.GetArray())
//		{
//			ConstructBlueprint(blueprint);
//		}
//	}
//	else if (document.IsObject())
//	{
//		ConstructBlueprint(document);
//	}
//}

void EntityFactory::ConstructBlueprint(const rapidjson::Value& value)
{
	EntityBlueprint blueprint;
	blueprint.Init(value);

	std::string blueprintID = value["id"].GetString();
	RegisterBlueprint(blueprintID, blueprint);
}

Entity EntityFactory::Create(const char* name)
{
	Entity entity = m_entityManager.Create();

	auto blueprint = m_blueprints.find(name);

	assert(blueprint != m_blueprints.end() && "Blueprint not found");

	const auto& componentProperties = blueprint->second.GetComponentProperties();
	for (const auto& [component, properties] : componentProperties)
	{
		// m_ecs.AddComponent(entity, component.c_str()); // fix string!

		auto itr = m_componentRegistry.find(component);

		if (itr == m_componentRegistry.end())
			continue;
		
		itr->second.AddComponent(entity);

		if (!properties.empty()) // Todo, also put checks in ComponentInitailizer!
		{
			itr->second.InitializeComponent(entity, properties);
		}
	}

	return entity;
}

Entity EntityFactory::CreateFromJson(const rapidjson::Value& value)
{
	// maybe not??
	const char* id = value["entity_id"].GetString();
	Entity entity = Create(id); // dont call this? or refactor function?? or fine since json only overrides some values?

	//Entity entity = m_ecs.CreateEmptyEntity();

	if (value.HasMember("components_data"))
	{
		for (const auto& component : value["components_data"].GetArray())
		{
			ComponentProperties componentProperties;

			for (const auto& [key, value] : component["properties"].GetObj())
			{
				Property property = EntityBlueprint::ParseProperty(value);
				componentProperties.insert({ key.GetString(), property });
			}
			// move initialization to entity factory?? asdadasdas

			//auto type = m_componentTypeMap.find(component["type"].GetString());

			auto itr = m_componentRegistry.find(component["type"].GetString());
			// assert(itr != registry.end() && "[ECS - ERROR]: Couldn't find component type in ComponentRegistry!");

			itr->second.InitializeComponent(entity, componentProperties);

			//m_ecs.InitializeComponent(entity, component["type"].GetString(), componentProperties);
		}
	}

	return entity;
}

//Entity EntityFactory::Create(const char* name, const rapidjson::Value& value)
//{
//	Entity entity = m_ecs.CreateEmptyEntity();
//
//	auto blueprint = m_blueprints.find(name);
//
//	assert(blueprint != m_blueprints.end() && "Blueprint not found");
//
//	
//	for (const auto& component : value["components_data"].GetArray())
//	{
//
//	}
//
//	return entity;
//}

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

//ComponentProperties EntityFactory::ParseComponent(const rapidjson::Value& value)
//{
//	assert(value.IsObject() && "ERROR: Parsing Component");
//	ComponentData data;
//
//	for (auto& property : value.GetObject())
//	{
//		const std::string key = property.name.GetString();
//		data.insert_or_assign(key, Hi_Engine::ParseJson(property.value));
//	}
//
//	return data;
//}