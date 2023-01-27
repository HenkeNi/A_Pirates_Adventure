#pragma once
#include "../Data/Enumerations.h"

class SceneManager;

class SceneManagerProxy
{
public:
	SceneManagerProxy(SceneManager& aSceneManager);

	void Push(eSceneType aType);
	void Pop();
	void SwapTo(eSceneType aType);
	void Clear();
	bool IsEmpty()	const;

private:
	SceneManager& m_sceneManager;
};