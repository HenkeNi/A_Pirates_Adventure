#pragma once
#include "../Data/Enumerations.h"
//  #include <Hi_Engine.h>
#include <Utility/DataStructures/Linear/Dynamic/Stack/Stack.hpp>

namespace CU = CommonUtilities;

class Scene;

namespace
{
	using ScenePtr_t = std::unique_ptr<Scene>;
}

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	// LoadScene("MainMenu"	);

	void Init(int aSceneSet);					
	void Register(ScenePtr_t aScene, eScene aType);
	void Push(eScene aType);
	void Pop();
	void SwapTo(eScene aType);
	void Clear();
	bool IsEmpty()			const;

	void Update(float aDeltaTime);	
	void LateUpdate(float aDeltaTime);
	void Draw()				const;

	//void LoadScene();
	// void UnloadScene()

private:
	void LoadScenes();

	// SceneFactory??

	std::unordered_map<eScene, ScenePtr_t>	m_scenes;
	CU::Stack<eScene>						m_sceneStack;
};