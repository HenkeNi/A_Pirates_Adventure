#include "Pch.h"
#include "EntityManager.h"
#include "Entity.h"
#include "../PostMaster/Message.h"
#include "../PostMaster/PostMaster.h"

#include "Rendering/RenderComponents.h"
#include "Core/CoreComponents.h"
#include "Controllers/ControllerComponents.h"
#include "Physics/PhysicsComponents.h"


EntityFactory EntityManager::s_entityFactory;


EntityManager::EntityManager()
{
	m_entities.reserve(200);
}

EntityManager::~EntityManager()
{
}

void EntityManager::LoadBlueprints(const std::string& aFilePath)
{
	auto loadBlueprintsFromJson = [](const std::string& aFilePath)
	{
		std::ifstream ifs{ aFilePath };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		document.Parse(content.c_str());

		assert(!document.HasParseError() && "Failed to parse Blueprints");

		std::string identifier = document["name"].GetString();

		EntityBlueprint blueprint;

		for (auto& componentType : document["components"].GetArray())
		{
			blueprint.AddComponentType(componentType.GetString());
		}

		// TODO; find a way to read the component_data!!

		s_entityFactory.RegisterBlueprint(identifier, blueprint);
	};

	std::ifstream ifs{ aFilePath };
	std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

	rapidjson::Document document;
	document.Parse(content.c_str());

	assert(!document.HasParseError() && "Failed to parse Blueprints");
	
	for (auto& blueprint : document["blueprints"]["player"].GetArray())
	{
		std::string path = blueprint.GetString();
		loadBlueprintsFromJson(path);
	}

	for (auto& blueprint : document["blueprints"]["enemies"].GetArray())
	{
		std::string path = blueprint.GetString();
		loadBlueprintsFromJson(path);
	}

	for (auto& blueprint : document["blueprints"]["props"].GetArray())
	{
		std::string path = blueprint.GetString();
		loadBlueprintsFromJson(path);
	}
}

void EntityManager::RegisterComponentBuilders()
{
	s_entityFactory.RegisterComponentBuilder("Sprite",				new ConcreteComponentBuilder<SpriteComponent>());
	s_entityFactory.RegisterComponentBuilder("Transform",			new ConcreteComponentBuilder<TransformComponent>());
	s_entityFactory.RegisterComponentBuilder("Input",				new ConcreteComponentBuilder<InputComponent>());
	s_entityFactory.RegisterComponentBuilder("Animation",			new ConcreteComponentBuilder<AnimationComponent>());

	s_entityFactory.RegisterComponentBuilder("PlayerController",	new ConcreteComponentBuilder<PlayerControllerComponent>());
	s_entityFactory.RegisterComponentBuilder("Velocity",			new ConcreteComponentBuilder<VelocityComponent>());
}



// TODO; remove later??
void EntityManager::Add(Entity anEntity)
{
	m_entities.push_back(std::move(anEntity));

	PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityCreated, &m_entities.back() }); // REMOVE!!
}


Entity* EntityManager::Create(const std::string& aType)
{
	auto entity = s_entityFactory.Create(aType);

	m_entities.push_back(std::move(entity));

	auto* created = &m_entities.back();
	PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityCreated, created });

	return created;
}

Entity* EntityManager::Find(unsigned anID)
{
	auto it = std::find_if(m_entities.begin(), m_entities.end(), [=](const Entity& anEntity) { return anEntity.GetID() == anID; });

	if (it != m_entities.end())
		return &(*it);

	return nullptr;
}

void EntityManager::Destroy(unsigned anID)
{
	auto it = std::find_if(m_entities.begin(), m_entities.end(), [=](const Entity& anEntity) { return anEntity.GetID() == anID; });

	if (it != m_entities.end())
	{
		PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityDestroyed, &(*it) });
		m_entities.erase(it);
	}
}

void EntityManager::DestroyAll()
{
	m_entities.clear();
}