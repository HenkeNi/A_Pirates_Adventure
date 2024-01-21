#pragma once
#include "../DataTypes/Enumerations.h"

class SceneManager;

// REMOVE? renamee SceneManagerInterface?
class SceneManagerProxy
{
public:
	SceneManagerProxy(SceneManager& aSceneManager);

	void Push(eScene aType);
	void Pop();
	void SwapTo(eScene aType);
	void Clear();

private:
	SceneManager& m_sceneManager;
};