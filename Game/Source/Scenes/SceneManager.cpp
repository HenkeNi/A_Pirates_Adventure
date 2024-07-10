#include "Pch.h"
#include "SceneManager.h"
#include "Registration/Registration.h"
#include "Scene.h"

#include "ECS/ECS.h"
#include "Entities/EntityManager.h"
#include "Entities/EntityFactory.h"
#include "Systems/SystemManager.h"
#include "../DataTypes/Enumerations.h"

static std::unordered_map<eScene, std::string> scenePaths
{
	{ eScene::Inventory,	"../Game/Assets/Json/Scenes/Inventory.json"	},
	{ eScene::Settings,		"../Game/Assets/Json/Scenes/Settings.json"	},
	{ eScene::Menu,			"../Game/Assets/Json/Scenes/MainMenu.json"	},
	{ eScene::Title,		"../Game/Assets/Json/Scenes/Title.json"		},
	{ eScene::Game,			"../Game/Assets/Json/Scenes/Game.json"		}
};

SceneManager::SceneManager()
{
	PostMaster::GetInstance().Subscribe(eMessage::TransitionToScene, this);
}

SceneManager::~SceneManager()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::TransitionToScene, this);
}

void SceneManager::Receive(Message& message)
{
	auto sceneType = std::any_cast<eScene>(message.GetData());

	if (!m_registeredScenes.contains(sceneType))
		return;

	auto sceneItr = std::find_if(m_activeScenes.begin(), m_activeScenes.end(), 
		[&](const eScene& scene) 
		{ 
			return scene == sceneType; 
		});

	if (sceneItr == m_activeScenes.end())
	{
		Push(sceneType);
	}
	else 
	{
		/* if not current scene */
		if (*sceneItr != m_activeScenes.back())
			Pop();
	}
}

void SceneManager::Init(const std::initializer_list<eScene>& scenes)
{
	for (const auto scene : scenes)
		m_activeScenes.push_back(scene);
}

void SceneManager::Shutdown()
{
	for (auto& [type, scene] : m_registeredScenes)
	{
		if (scene)
			scene->OnDestroyed();
	}

	m_activeScenes.clear();
}

std::weak_ptr<const Scene> SceneManager::GetActiveScene() const
{
	if (!m_activeScenes.empty())
		return m_registeredScenes.at(m_activeScenes.back());

	return std::weak_ptr<Scene>();
}

std::weak_ptr<Scene> SceneManager::GetActiveScene()
{
	if (!m_activeScenes.empty())
		return m_registeredScenes.at(m_activeScenes.back());

	return std::weak_ptr<Scene>();
}

void SceneManager::TransitionToScene(eScene type)
{
	if (scenePaths.contains(type))
	{
		LoadScene(type);
	}

	m_registeredScenes[type]->OnEnter();
}

void SceneManager::Push(eScene type)
{
	if (!m_activeScenes.empty())
	{
		m_registeredScenes[m_activeScenes.back()]->OnExit();
	}

	m_activeScenes.push_back(type);
	TransitionToScene(m_activeScenes.back());	
}

void SceneManager::Pop()
{
	if (!m_activeScenes.empty()) 
	{
		m_registeredScenes[m_activeScenes.back()]->OnExit();
		m_activeScenes.pop_back();

		TransitionToScene(m_activeScenes.back());
	}
}

void SceneManager::SwapTo(eScene type)
{
	if (!m_activeScenes.empty())
	{
		m_registeredScenes[m_activeScenes.back()]->OnExit();
		m_activeScenes.pop_back();
	}

	m_activeScenes.push_back(type);
	
	TransitionToScene(type);
}

void SceneManager::LoadScene(eScene type)
{
	auto activeScene = GetActiveScene().lock();
	if (!activeScene)
		return;

	// TODO; Move some of this stuff to ECS???
	auto& entityManager = activeScene->m_ecs.GetEntityManager();
	auto& entityFactory = activeScene->m_ecs.GetEntityFactory();
	auto& systemManager = activeScene->m_ecs.GetSystemManager();
	
	systemManager.Clear();
	// entityManager.DestroyAll(); 

	const auto& path = scenePaths.at(type);
	auto document = Hi_Engine::ParseDocument(path);

	for (const auto& system : document["systems"].GetArray())
	{
		systemManager.Create(system.GetString());
	}

	systemManager.Init(&entityManager); // FIX!

	for (const auto& jsonEntity : document["entities"].GetArray())
	{
		std::string id = jsonEntity["entity_id"].GetString();
		
		auto* entity = entityManager.Create(id);

		if (!jsonEntity.HasMember("components_data"))
			continue;

		for (const auto& component : jsonEntity["components_data"].GetArray())
		{
			std::string type = component["type"].GetString();
			const rapidjson::Value& properties = component["properties"];

			auto componentData = EntityFactory::ParseComponent(properties); // dont static?

			auto* component = entityFactory.GetCompFactory().Build(type, componentData);
			entity->AddComponent(component);
		}

		// Send event spawned? Change to initailzied?
		PostMaster::GetInstance().SendMessage({ eMessage::EntitySpawned, entity });
	}
}