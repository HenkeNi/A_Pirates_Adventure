#pragma once
#include "SceneManager.h"

class Game : public Hi_Engine::Application
{
public:
	Game();
	~Game();

	void			OnUpdate(float aDeltaTime)		override;
	void			OnLateUpdate(float aDeltaTime)	override;
	void			OnDraw()						override;

	void			OnCreate()						override;
	void			OnDestroy()						override;

private:
	void			SetupScenes();

	SceneManager	m_sceneManager;
};

Hi_Engine::Application* Hi_Engine::CreateApplication()
{
	return new Game;
}