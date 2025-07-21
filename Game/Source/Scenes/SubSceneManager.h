#pragma once
#include <../Services/Scene/SceneTypes.h>
#include <../Services/Scene/SceneLoader.h>

namespace Hi_Engine
{
	class Scene;
}

using Hi_Engine::Scene;
using Hi_Engine::SceneID;

class SubSceneManager
{
public:
	template <DerivedFrom<Scene> T>
	void Insert(std::shared_ptr<Scene> scene);

	template <DerivedFrom<Scene> T, typename... Args>
	T& Emplace(Args&&... args);

	template <DerivedFrom<Scene> T>
	void Remove();

	void Clear();

	template <DerivedFrom<Scene> T>
	void SetActive();

	[[nodiscard]] std::weak_ptr<const Scene> GetActive() const;

	[[nodiscard]] std::weak_ptr<Scene> GetActive();

private:
	std::unordered_map<SceneID, std::shared_ptr<Scene>> m_subScenes;
	SceneID m_activeScene;
};

#pragma region Templated_Methods
 
template <DerivedFrom<Scene> T>
void SubSceneManager::Insert(std::shared_ptr<Scene> scene)
{
	auto sceneID = Hi_Engine::GetSceneID<T>();
	m_subScenes.insert({ sceneID, scene });
}

template <DerivedFrom<Scene> T, typename ...Args>
T& SubSceneManager::Emplace(Args && ...args)
{
	auto sceneID = Hi_Engine::GetSceneID<T>();
	auto scene = std::make_shared<T>(std::forward<Args>(args)...);

	m_subScenes.insert_or_assign(sceneID, scene);

	return *scene;
}

template <DerivedFrom<Scene> T>
void SubSceneManager::Remove()
{
}

template <DerivedFrom<Scene> T>
void SubSceneManager::SetActive()
{
	const SceneID id = Hi_Engine::GetSceneID<T>();

	m_activeScene = id;
	
	auto subScene = m_subScenes.at(id);

	Hi_Engine::SceneLoader sceneLoader;
	sceneLoader.Load(*subScene, id);

	//subScene->OnEnter();
}

#pragma endregion