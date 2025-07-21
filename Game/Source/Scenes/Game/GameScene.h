#pragma once
#include <../Services/Scene/Scene.h>
#include "SubSceneManager.h"

class GameScene : public Hi_Engine::Scene
{
public:
	GameScene(Hi_Engine::ServiceRegistry& registry);
	//~GameScene();

	void OnUpdate(float deltaTime)			  override;
	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;

	// TODO; store ui in game...?

private:
	SubSceneManager m_subSceneManager;
};