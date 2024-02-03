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
	void Receive(Message& aMsg) override;

	void Init(std::bitset<(int)eScene::Count> someScenes);
	void Register(MutableScene aScene, eScene aType);

	MutableScene GetActiveScene();
	ImmutableScene GetActiveScene() const;


	void Push(eScene aType);
	void Pop();
	void SwapTo(eScene aType);
	void Clear();


	// Scene& GetActiveScene();
	// void LoadScene();
	// void UnloadScene()

private:
	void LoadScenes();
	
	Scenes				m_scenes;			// STore by value?
	CU::Stack<eScene>	m_stack;
};