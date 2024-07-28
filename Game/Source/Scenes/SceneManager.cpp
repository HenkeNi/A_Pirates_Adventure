#include "Pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SceneTypes.h"
#include "ECS/ECS.h"

static std::unordered_map<eScene, std::string> scenePaths
{
	{ eScene::Inventory,	"../Game/Assets/Json/Scenes/Inventory.json"	},
	{ eScene::Settings,		"../Game/Assets/Json/Scenes/Settings.json"	},
	{ eScene::Menu,			"../Game/Assets/Json/Scenes/MainMenu.json"	},
	{ eScene::Title,		"../Game/Assets/Json/Scenes/Title.json"		},
	{ eScene::Overworld,	"../Game/Assets/Json/Scenes/Overworld.json"	}
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

	// TODO; scene loader class?

	activeScene->m_systems.clear();

	auto& ecs = activeScene->m_ecs;
	ecs.DestroySystems();

	auto foundPath = scenePaths.find(type);
	if (foundPath == scenePaths.end())
		return;

	auto document = Hi_Engine::ParseDocument(foundPath->second);

	for (const auto& system : document["systems"].GetArray())
	{
		bool isSystemAvailable = Hi_Engine::IsBuildDebug() ? system["debug"].GetBool() : system["release"].GetBool();

		if (isSystemAvailable)
		{
			auto* created = ecs.CreateSystem(system["type"].GetString());			
			activeScene->m_systems.push_back(created);
		}
	}

	for (const auto& jsonEntity : document["entities"].GetArray())
	{
		const char* id = jsonEntity["entity_id"].GetString();
		
		Entity entity = ecs.CreateEntity(id);

		if (!jsonEntity.HasMember("components_data"))
			continue;

		for (const auto& component : jsonEntity["components_data"].GetArray())
		{
			ComponentProperties componentProperties;
			
			for (const auto& [key, value] : component["properties"].GetObj())
			{
				Property property = EntityBlueprint::ParseProperty(value);
				componentProperties.insert({ key.GetString(), property });
			}
			ecs.InitializeComponent(entity, component["type"].GetString(), componentProperties);
		}

		PostMaster::GetInstance().SendMessage({ eMessage::EntitySpawned, entity }); // FIX!?
	}
}