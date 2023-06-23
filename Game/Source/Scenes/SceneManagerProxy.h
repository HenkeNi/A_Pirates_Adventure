#pragma once
#include "../Data/Enumerations.h"

class SceneManager;

class SceneManagerProxy
{
public:
	SceneManagerProxy(SceneManager& aSceneManager);

	void Push(eScene aType);
	void Pop();
	void SwapTo(eScene aType);
	void Clear();
	bool IsEmpty() const;

private:
	SceneManager& m_sceneManager;
};