#pragma once
#include <../Hi_Engine.h>

enum class eScene;
class Scene;

// REMOVE empty namespace?
namespace Utility
{
	using Scenes = std::unordered_map<eScene, std::shared_ptr<Scene>>;
}

class SceneManager : public Subscriber
{
private:

public:
	SceneManager();
	~SceneManager();

	void Receive(Message& message) override;

	template <typename T, typename... Args>
	void Register(eScene type, Args&&... args);
	void Init(const std::initializer_list<eScene>& scenes);

	std::shared_ptr<Scene> GetActiveScene();
	std::shared_ptr<const Scene> GetActiveScene() const;

	void Push(eScene type);
	void Pop();
	void SwapTo(eScene type);
	void Clear();

	void TransitionToScene(eScene type);

	// Scene& GetActiveScene();
	// void LoadScene();
	// LoadScene("MainMenu"	);
	// void UnloadScene()

private:
	void LoadScene(const std::string& aPath);

	Utility::Scenes				m_registeredScenes; // m_registeredScenes
	Hi_Engine::Stack<eScene>	m_stack;
	//std::vector<eScene> m_currentScenes;

	std::unordered_map<eScene, std::string> m_paths; // Function in scene?
};

#pragma region Method_Definitions

template <typename T, typename... Args>
void SceneManager::Register(eScene type, Args&&... args)
{
	m_registeredScenes.insert({ type, std::make_shared<T>(std::forward<Args>(args)...) });
}

#pragma endregion Method_Definitions