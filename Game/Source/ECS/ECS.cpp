#include "Pch.h"
#include "ECS.h"


ECS::ECS()
	: m_systemFactory{ *this }, m_entityFactory{ *this }
{
	// LoadBlueprints();
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

//Entity ECS::CreateEntity(const char* type, const rapidjson::Value& value)
//{
//	Entity entity = m_entityFactory.Create(type, value);
//
//	// TODO; update signature (event?)
//
//	return Entity();
//}

Entity ECS::CreateEmptyEntity()
{
	Entity entity = m_entityManager.Create();
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

void ECS::Serialize(const char* file)
{
	// save components...

	Hi_Engine::SerializeJson();

	//auto document = Hi_Engine::ParseDocument("../Game/Assets/Saved/Scenes/MainMenu.json");
	
	//const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
	//rapidDocument d;
	//d.Parse(json);

}

void ECS::Deserialize()
{
	// load components...
}

void ECS::AddComponent(Entity entity, const char* component)
{
	auto itr = m_componentRegistry.find(component);
	assert(itr != m_componentRegistry.end() && "[ECS - ERROR]: Couldn't find component type in ComponentRegistry!");

	itr->second.AddComponent(entity);
}

void ECS::InitializeComponent(Entity entity, const char* component, const ComponentProperties& properties)
{
	auto itr = m_componentRegistry.find(component);
	assert(itr != m_componentRegistry.end() && "[ECS - ERROR]: Couldn't find component type in ComponentRegistry!");

	itr->second.InitializeComponent(entity, properties);
	
	// m_componentManager.InitializeComponent(type, component, properties); // Dont store in componetn manager??
}

// void ECS::LoadSystems(const std::string& path)
//{
	// Call SystemManager??

	// Create systems (read from json)
	// make sure to call init with EntityManager!
//}
