#pragma once
#include <Core/Application/Application.h>
#include "Scenes/SceneManager.h"
#include "World/GameWorld.h"


class Game : public Hi_Engine::Application
{
public:
	Game();
	~Game();

	void OnUpdate(float aDeltaTime)		override;
	void OnLateUpdate(float aDeltaTime)	override;
	void OnDraw()						override;

	void OnCreate()						override;
	void OnDestroy()					override;

private:
	void SetupScenes();
	void LoadResources();
	void MapInput();

	//GameWorld		m_gameWorld;
	SceneManager	m_sceneManager;
};

//Hi_Engine::Application* Hi_Engine::CreateApplication()
//{
//	return new class Game; // new Game
//}