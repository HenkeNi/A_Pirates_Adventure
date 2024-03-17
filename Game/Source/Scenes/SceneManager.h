#pragma once
#include "../DataTypes/Enumerations.h"
//  #include <Hi_Engine.h>
#include <Utility/DataStructures/Linear/Dynamic/Stack/Stack.hpp>
#include <bitset>

namespace CU = CommonUtilities;

class Scene;

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
	//void Init(int aSceneSet);					
	void Receive(Message& message) override;

	void Init(std::bitset<(int)eScene::Count> scenes);
	void Register(MutableScene scene, eScene type);

	MutableScene GetActiveScene();
	ImmutableScene GetActiveScene() const;


	void Push(eScene type);
	void Pop();
	void SwapTo(eScene type);
	void Clear();


	// Scene& GetActiveScene();
	// void LoadScene();
	// void UnloadScene()

private:
	void LoadScenes();
	
	Scenes				m_scenes;			// STore by value?
	CU::Stack<eScene>	m_stack;
};