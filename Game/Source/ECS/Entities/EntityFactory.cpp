#include "Pch.h"
#include "EntityFactory.h"

ECS::ComponentData ParseComponent(const rapidjson::Value& aValue);

EntityFactory::EntityFactory()
{
	PostMaster::GetInstance().Subscribe(eMessage::ComponentBuilderCreated, this);
	PostMaster::GetInstance().Subscribe(eMessage::MultipleComponentBuildersCreated, this);
}

EntityFactory::~EntityFactory()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::ComponentBuilderCreated, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::MultipleComponentBuildersCreated, this);
}
	
void EntityFactory::Receive(Message& aMsg)
{
	if (aMsg.GetMessageType() == eMessage::ComponentBuilderCreated)
	{
		auto builder = std::any_cast<std::pair<std::string, ComponentBuilder*>>(aMsg.GetData());
		RegisterComponentBuilder(builder.first, builder.second);
	}

	if (aMsg.GetMessageType() == eMessage::MultipleComponentBuildersCreated)
	{
		auto builders = std::any_cast<std::vector<std::pair<std::string, ComponentBuilder*>>>(aMsg.GetData());

		for (const auto& [type, builder] : builders)
		{
			RegisterComponentBuilder(type, builder);
		}
	}
}

void EntityFactory::LoadBlueprints(const std::string& aPath)
{
	auto document = CommonUtilities::ParseDocument(aPath);

	for (auto& category : document["blueprints"].GetObject())
	{	
		for (auto& blueprint : category.value.GetArray())
		{
			LoadBlueprint(blueprint.GetString());
		}
	}
}

void EntityFactory::LoadBlueprint(const std::string& aPath)
 {
	EntityBlueprint blueprint;

	auto document = CommonUtilities::ParseDocument(aPath);
	for (auto& component : document["components"].GetArray())
	{
		const rapidjson::Value& properties = component["properties"];
		assert(properties.IsObject() && "Failed to load component properties for blueprint");

		blueprint.AddComponentData(component["type"].GetString(), ParseComponent(properties));
	}

	std::string blueprintID = document["id"].GetString();
	RegisterBlueprint(blueprintID, blueprint);

	// TODO. store type ("type: "transform") in COmponent base?
}

Entity EntityFactory::Create(const ECS::EntityType& aType)
{
	auto found = m_blueprints.find(aType);

	assert(found != m_blueprints.end() && "ERROR: Failed to create entity - Couldn't find blueprint!");
	Entity entity;

	for (const auto& [type, data] : found->second.m_componentData)
	{
		auto* component = m_componentFactory.Build(type, data);
		entity.AddComponent(component);
	}

	return entity;
}

Entity EntityFactory::CreateFromBlueprint(const EntityBlueprint& aBlueprint)
{
	Entity entity;
	
	for (const auto& [type, data] : aBlueprint.m_componentData)
	{
		auto* component = m_componentFactory.Build(type, data);
		entity.AddComponent(component);
	}

	return entity;
}

void EntityFactory::RegisterBlueprint(const std::string& anID, EntityBlueprint aBlueprint)
{
	m_blueprints.insert_or_assign(anID, std::move(aBlueprint));
}

void EntityFactory::RegisterComponentBuilder(const std::string& aType, ComponentBuilder* aBuilder)
{
	m_componentFactory.RegisterBuilder(aType, aBuilder);
}

ECS::ComponentData ParseComponent(const rapidjson::Value& aValue)
{
	assert(aValue.IsObject() && "ERROR: Parsing Component");
	ECS::ComponentData data;

	for (auto& property : aValue.GetObject())
	{
		const std::string key = property.name.GetString();
		data.insert_or_assign(key, CommonUtilities::ParseJson(property.value));
	}

	return data;
}