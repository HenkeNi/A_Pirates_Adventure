#pragma once
#include <../Scene/Scene.h>
//#include "../Scene.h"
//#include "../SceneManager.h"


class GameScene : public Hi_Engine::Scene
{
public:
	//GameScene(Hi_Engine::ECSCoordinator& ecs);
	//~GameScene();

	void Update(float deltaTime)			  override;
	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;

private:
	//SceneManager m_sceneManager;
};