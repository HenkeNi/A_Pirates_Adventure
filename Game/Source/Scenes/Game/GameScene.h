#pragma once
#include "../Scene.h"
#include "../SceneManager.h"


class GameScene : public Scene
{
public:
	//GameScene(Hi_Engine::ECSCoordinator& ecs);
	//~GameScene();

	void Update(float deltaTime)			  override;
	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;

private:
	SceneManager m_sceneManager;
};