#include "Pch.h"
#include "ECS.h"


ECS::ECS()
	: m_systemFactory{ *this }, m_entityFactory{ m_entityManager, m_componentRegistry }
{
}

void ECS::Init()
{
	m_entityFactory.LoadBlueprints();
}

void ECS::Shutdown() 
{
	m_systemManager.RemoveAllSystem();
	DestroyAllEntities();
}

void ECS::Serialize(const char* file)
{
	m_componentManager.SerializeComponents(m_componentRegistry);

	// save components...

	// Hi_Engine::SerializeJson();

	//auto document = Hi_Engine::ParseDocument("../Game/Assets/Saved/Scenes/MainMenu.json");

	//const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
	//rapidDocument d;
	//d.Parse(json);

}

void ECS::Deserialize()
{
	// load components...
}

std::weak_ptr<System> ECS::GetSystem(const char* system)
{
	return m_systemManager.GetSystem(system);
}

//System* ECS::CreateSystem(const char* type)
//{
//	if (auto* system = m_systemFactory.Create(type))
//	{
//		m_systemManager.AddSystem(system);
//		return system;
//	}
//
//	return nullptr;
//}

Entity ECS::CreateEntity(const char* type, bool notify)
{
	Entity entity = m_entityFactory.Create(type);

	if (notify)
		PostMaster::GetInstance().SendMessage({ eMessage::EntityCreated, entity });

	return entity;
}

Entity ECS::CreateEntityFromJson(const rapidjson::Value& jsonEntity)
{
	Entity entity = m_entityFactory.CreateFromJson(jsonEntity);

	PostMaster::GetInstance().SendMessage({ eMessage::EntityCreated, entity });

	return entity;
}

//Entity ECS::CreateEntity(const char* type, const rapidjson::Value& value)
//{
//	Entity entity = m_entityFactory.Create(type, value);
//
//	// TODO; update signature (event?)
//
//	return Entity();
//}


//void ECS::DestroySystems()
//{
//	//m_systemManager.Clear();
//}

std::vector<Entity> ECS::FindEntities(const Signature& signature)
{
	auto entities = m_entityManager.GetEntities(signature);
	return entities;
}

std::optional<Entity> ECS::FindEntity(const Signature& signature)
{
	std::optional<Entity> entity = m_entityManager.GetEntity(signature);
	return entity;
}

void ECS::DestroyAllEntities()
{
	auto entities = m_entityManager.GetActiveEntities();

	for (Entity entity : entities)
	{
		m_componentManager.RemoveAllComponents(entity);
	}

	m_entityManager.DestroyAll();
}

void ECS::DestroyEntity(Entity entity)
{
	m_componentManager.RemoveAllComponents(entity);
	m_entityManager.Destroy(entity);
}


//void ECS::LoadBlueprints()
//{
//	const char* path = "../Game/Assets/Json/Blueprints/blueprint_manifest.json";
//
//	auto document = Hi_Engine::ParseDocument(path);
//
//	for (auto& path : document["blueprints"].GetArray())
//	{
//		std::string blueprintPath = path.GetString();
//		m_entityFactory.LoadBlueprint(blueprintPath);
//	}
//}

// void ECS::LoadSystems(const std::string& path)
//{
	// Call SystemManager??

	// Create systems (read from json)
	// make sure to call init with EntityManager!
//}
