#include "Pch.h"
#include "SceneService.h"
#include "Scene.h"
#include "SceneLoader.h"

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

	void SceneService::Clear()
	{
	}

	void SceneService::SetActiveScenes(std::initializer_list<SceneID> scenes)
	{
		for (const auto scene : scenes)
			m_activeScenes.push_back(scene);
	}

	void SceneService::Shutdown() noexcept
	{
		for (auto& [type, scene] : m_scenes)
		{
			if (scene)
				scene->OnDestroyed();
		}

		m_activeScenes.clear();
	}

	void SceneService::TransitionTo(SceneID id) // or replace current scene??
	{
		// TEMP
		if (m_activeScenes.back() != id)
			m_scenes[m_activeScenes.back()]->OnExit();

		// TEMP:::
		auto found = std::find(m_activeScenes.begin(), m_activeScenes.end(), id);
		if (found == m_activeScenes.end())
			m_activeScenes.push_back(id);
		else
		{
			while(m_activeScenes.back() != id)
				m_activeScenes.pop_back();
		}

		
		if (auto scene = m_scenes[id])
		{
			SceneLoader sceneLoader;
			sceneLoader.Load(*scene, id);
			
			m_scenes[id]->OnEnter();
		}
		// else throw error?

		//SceneLoader::LoadScene(id, { scene->GetWorld(), scene->})

		// TODO; add to active scnees?
		//if (scenePaths.contains(id))
		//{
		//	LoadScene(id); // Dont?
		//}

	}

	void SceneService::Push(SceneID id)
	{
		if (!m_activeScenes.empty())
		{
			m_scenes[m_activeScenes.back()]->OnExit();
		}

		m_activeScenes.push_back(id);
		TransitionTo(m_activeScenes.back());
	}

	void SceneService::Pop()
	{
		if (!m_activeScenes.empty())
		{
			m_scenes[m_activeScenes.back()]->OnExit();
			m_activeScenes.pop_back();

			TransitionTo(m_activeScenes.back());
		}
	}

	void SceneService::SwapTo(SceneID id)
	{
		if (!m_activeScenes.empty())
		{
			m_scenes[m_activeScenes.back()]->OnExit();
			m_activeScenes.pop_back();
		}

		m_activeScenes.push_back(id);

		TransitionTo(id);
	}

	std::weak_ptr<const Scene> SceneService::GetActive() const
	{
		if (!m_activeScenes.empty())
			return m_scenes.at(m_activeScenes.back());

		return std::weak_ptr<Scene>();
	}

	std::weak_ptr<Scene> SceneService::GetActive()
	{
		// TOOD; const cast??

		if (!m_activeScenes.empty())
			return m_scenes.at(m_activeScenes.back());

		return std::weak_ptr<Scene>();
	}

	/*void SceneService::LoadScene(SceneID id)
	{
	}

	void SceneService::UnloadScene(SceneID id)
	{
	}*/
}