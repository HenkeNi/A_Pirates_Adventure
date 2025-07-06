#pragma once
#include <../Services/Scene/Scene.h>
//#include <../Scene/Scene.h>
//#include "../Scene.h"
//#include "../SceneManager.h"


class GameScene : public Hi_Engine::Scene
{
public:
	//GameScene(Hi_Engine::ECSCoordinator& ecs);
	//~GameScene();

	void OnUpdate(float deltaTime)			  override;
	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;

private:
	//SceneManager m_sceneManager; -> how to deal with "nested" scene managers?
};