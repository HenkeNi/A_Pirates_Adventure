#pragma once
#include "../Data/Enumerations.h"
//  #include <Hi_Engine.h>
#include <Utility/DataStructures/Linear/Dynamic/Stack/Stack.hpp>

#include <bitset>

namespace CU = CommonUtilities;

class Scene;

namespace
{
	using SceneMap = std::unordered_map<eScene, std::shared_ptr<Scene>>;
	using ScenePtr_t = std::shared_ptr<Scene>;
	//using ScenePtr_t = std::unique_ptr<Scene>;
}

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	// LoadScene("MainMenu"	);

	//void Init(int aSceneSet);					
	void Init(std::bitset<(int)eScene::Count> someScenes);
	void Register(ScenePtr_t aScene, eScene aType);
	void Push(eScene aType);
	void Pop();
	void SwapTo(eScene aType);
	void Clear();
	bool IsEmpty()			const;

	//void Update(float aDeltaTime);	
	//void LateUpdate(float aDeltaTime);
	//void Draw()				const;


	std::shared_ptr<Scene>		 GetActiveScene();
	std::shared_ptr<const Scene> GetActiveScene() const;

	//Scene& GetActiveScene();
	//void LoadScene();
	// void UnloadScene()

private:
	void LoadScenes();

	// SceneFactory??

	
		
	SceneMap			m_scenes;			// STore by value?
	CU::Stack<eScene>	m_sceneStack;
};