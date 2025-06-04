#include "Pch.h"
#include "SceneManager.h"
#include "Scene.h"
//#include "SceneTypes.h"
//#include "ECS/ECS.h"

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
		// TODO; add to active scnees?

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

		//auto document = JsonUtils::LoadJsonDocument();
		
		// TODO; scene loader class?
		// Clear scene? or on exit (do in scene if needed)?

		// auto& world = activeScene->LoadFromJson();


		//auto foundPath = scenePaths.find(id);
		//if (foundPath == scenePaths.end())
		//	return;

		//auto document = Hi_Engine::LoadJsonDocument(foundPath->second);

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

			// Hi_Engine::EngineFacade::FromJson(jsonEntity);
		}
	}
}