#include "Pch.h"
#include "SceneManager.h"
#include "Scene.h"
//#include "SceneTypes.h"
//#include "ECS/ECS.h"

//static std::unordered_map<eScene, std::string> scenePaths
//{
//	//{ eScene::Inventory,	"../Game/Assets/Json/Scenes/Inventory.json"	},
//	//{ eScene::Settings,		"../Game/Assets/Json/Scenes/Settings.json"	},
//	//{ eScene::Menu,			"../Game/Assets/Json/Scenes/MainMenu.json"	},
//	//{ eScene::Title,		"../Game/Assets/Json/Scenes/Title.json"		},
//	//{ eScene::Overworld,	"../Game/Assets/Json/Scenes/Overworld.json"	}
//};

namespace Hi_Engine
{


	//void SceneManager::Receive(Message& message)
	//{
	//	auto sceneType = std::any_cast<eScene>(message.GetData());

	//	if (!m_registeredScenes.contains(sceneType))
	//		return;

	//	auto sceneItr = std::find_if(m_activeScenes.begin(), m_activeScenes.end(),
	//		[&](const eScene& scene)
	//		{
	//			return scene == sceneType;
	//		});

	//	if (sceneItr == m_activeScenes.end())
	//	{
	//		Push(sceneType);
	//	}
	//	else
	//	{
	//		/* if not current scene */
	//		if (*sceneItr != m_activeScenes.back())
	//			Pop();
	//	}
	//}

	void SceneManager::Init(std::initializer_list<SceneID> scenes)
	{
		for (const auto scene : scenes)
			m_activeScenes.push_back(scene);
	}

	void SceneManager::Shutdown()
	{
		for (auto& [type, scene] : m_scenes)
		{
			if (scene)
				scene->OnDestroyed();
		}

		m_activeScenes.clear();
	}

	std::weak_ptr<const Scene> SceneManager::GetActive() const
	{
		if (!m_activeScenes.empty())
			return m_scenes.at(m_activeScenes.back());

		return std::weak_ptr<Scene>();
	}

	std::weak_ptr<Scene> SceneManager::GetActive()
	{
		if (!m_activeScenes.empty())
			return m_scenes.at(m_activeScenes.back());

		return std::weak_ptr<Scene>();
	}

	void SceneManager::TransitionTo(SceneID id)
	{
		//if (scenePaths.contains(id))
		{
			LoadScene(id);
		}

		m_scenes[id]->OnEnter();
	}

	void SceneManager::Push(SceneID id)
	{
		if (!m_activeScenes.empty())
		{
			m_scenes[m_activeScenes.back()]->OnExit();
		}

		m_activeScenes.push_back(id);
		TransitionTo(m_activeScenes.back());
	}

	void SceneManager::Pop()
	{
		if (!m_activeScenes.empty())
		{
			m_scenes[m_activeScenes.back()]->OnExit();
			m_activeScenes.pop_back();

			TransitionTo(m_activeScenes.back());
		}
	}

	void SceneManager::SwapTo(SceneID id)
	{
		if (!m_activeScenes.empty())
		{
			m_scenes[m_activeScenes.back()]->OnExit();
			m_activeScenes.pop_back();
		}

		m_activeScenes.push_back(id);

		TransitionTo(id);
	}

	void SceneManager::LoadScene(SceneID id)
	{
		auto activeScene = GetActive().lock();

		if (!activeScene)
			return;

		// TODO; scene loader class?
		// auto ecs = Hi_Engine::EngineFacade::GetECS().lock();

		//if (!ecs)
		//{
		//	int xx = 20;
		//	xx += 20;
		//}

		//activeScene->m_systems.clear();
		//auto& ecs = activeScene->m_ecs;

		//ecs.DestroySystems();

		//auto foundPath = scenePaths.find(id);
		//if (foundPath == scenePaths.end())
		//	return;

		//auto document = Hi_Engine::ParseDocument(foundPath->second);

		//// temp

		//for (const auto& system : document["systems"].GetArray())
		//{
		//	bool isSystemAvailable = Hi_Engine::IsBuildDebug() ? system["debug"].GetBool() : system["release"].GetBool();

		//	if (isSystemAvailable)
		//	{
		//		auto systemType = system["type"].GetString();
		//		
		//		auto found = ecs.GetSystem(systemType); // TODO; check nullptr

		//		if (!found.expired())
		//			activeScene->m_systems.push_back(found);
		//		else
		//			std::cout << "ERROR: invalid scene\n"; // log class..
		//	}
		//}

		// read sounds as well?

		// sort systems here??

		//for (const auto& jsonEntity : document["entities"].GetArray())
		{
			// ecs->CreateEntityFromJson(jsonEntity);

			// Hi_Engine::EngineFacade::CreateEntityFromJson(jsonEntity);
		}
	}
}