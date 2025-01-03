#pragma once
#include "Scenes/SceneManager.h"
#include <Application/Application.h>

class Game : public Hi_Engine::Application
{
public:
	Game();
	~Game();

	void OnUpdate(float deltaTime)		override;

	void OnCreate()						override;
	void OnDestroy()					override;

private:
	void LoadResources();

	SceneManager m_sceneManager;
};