#pragma once
#include "../Data/Enumerations.h"
#include <Hi_Engine.h>

namespace CU = CommonUtilities;

class Scene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init(std::initializer_list<eSceneType> aList);					// TODO; add bitset of eSceneType??
	void Register(std::unique_ptr<Scene> aScene, eSceneType aType);
	void Push(eSceneType aType);
	void Pop();
	void SwapTo(eSceneType aType);

	void Update(float aDeltaTime);	
	void LateUpdate(float aDeltaTime);
	void Draw()														const;
	bool IsEmpty()													const;
	void Clear();

private:
	std::array<std::unique_ptr<Scene>, (int)eSceneType::Count>	m_scenes;
	CU::Stack<eSceneType>										m_sceneStack;
};

// TODO: Add ProcessEvents() ??
// Change back m_scenes to unique_ptrs??
