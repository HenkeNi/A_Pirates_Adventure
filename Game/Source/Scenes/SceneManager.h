#pragma once
#include "PostMaster/Subscriber.h"
#include "Scene.h"

enum class eScene;
class Scene;

namespace Utility
{
	using Scenes = std::unordered_map<eScene, std::shared_ptr<Scene>>;
}

class SceneManager : public Subscriber
{
public:
	SceneManager();
	~SceneManager();

	void Receive(Message& message) override;

	template <typename T, typename... Args>
	void Register(eScene type, Args&&... args);
	void Init(const std::initializer_list<eScene>& scenes);
	void Shutdown();

	std::weak_ptr<const Scene> GetActiveScene() const;
	std::weak_ptr<Scene> GetActiveScene();

	void TransitionToScene(eScene type);
	void Push(eScene type);
	void Pop();
	void SwapTo(eScene type);

private:
	void LoadScene(eScene type);

	Utility::Scenes m_registeredScenes;
	std::vector<eScene> m_activeScenes;
};

#pragma region Method_Definitions

template <typename T, typename... Args>
void SceneManager::Register(eScene type, Args&&... args)
{
	m_registeredScenes.insert({ type, std::make_shared<T>(std::forward<Args>(args)...) });
	m_registeredScenes[type]->OnCreated();
}

#pragma endregion Method_Definitions