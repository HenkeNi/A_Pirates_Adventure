#pragma once
#include <Core/Application/Application.h>
#include "ECS/Systems/SystemManager.h"
#include "Scenes/SceneManager.h"


class Game : public Hi_Engine::Application
{
public:
	Game();
	~Game();

	void OnUpdate(float deltaTime)		override;
	void OnLateUpdate(float deltaTime)	override;
	void OnDraw()						override;

	void OnCreate()						override;
	void OnDestroy()					override;

private:
	void LoadResources();

	SystemManager	m_systemManager;
	SceneManager	m_sceneManager;
};