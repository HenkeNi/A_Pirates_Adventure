#pragma once
#include "../DataTypes/Enumerations.h"
#include <Utility/DataStructures/Linear/Dynamic/Stack/Stack.hpp>
#include <bitset>


namespace CU = CommonUtilities;

class Scene;

// REMOVE empty namespace?
namespace
{
	using Scenes = std::unordered_map<eScene, std::shared_ptr<Scene>>;

	using MutableScene	 = std::shared_ptr<Scene>;
	using ImmutableScene = std::shared_ptr<const Scene>;
}

class SceneManager : public Subscriber
{
public:
	SceneManager();
	~SceneManager();

	// LoadScene("MainMenu"	);
	void Receive(Message& message) override;

	template <typename T, typename... Args>
	void Register(eScene type, Args&&... args);
	void Init(std::initializer_list<eScene> scenes);

	//void Init(int aSceneSet);					
	//void Register(MutableScene scene, eScene type); // pass in path?
	
	MutableScene GetActiveScene();
	ImmutableScene GetActiveScene() const;


	void Push(eScene type);
	void Pop();
	void SwapTo(eScene type);
	void Clear();

	void TransitionToScene(eScene type);


	// Scene& GetActiveScene();
	// void LoadScene();
	// void UnloadScene()

private:
	void LoadEntities(const std::string& aPath);
	
	Scenes				m_scenes; // m_registeredScenes
	CU::Stack<eScene>	m_stack;
	//std::vector<eScene> m_currentScenes;

	std::unordered_map<eScene, std::string> m_paths; // Function in scene?
};

#pragma region Method_Definitions

template <typename T, typename... Args>
void SceneManager::Register(eScene type, Args&&... args)
{
	m_scenes.insert({ type, std::make_shared<T>(std::forward<Args>(args)...) });
}

#pragma endregion Method_Definitions