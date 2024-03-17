#pragma once
#include "../DataTypes/Enumerations.h"

class SceneManager;

// REMOVE? renamee SceneManagerInterface?
class SceneManagerProxy
{
public:
	SceneManagerProxy(SceneManager& sceneManager);

	void Push(eScene type);
	void Pop();
	void SwapTo(eScene type);
	void Clear();

private:
	SceneManager& m_sceneManager;
};