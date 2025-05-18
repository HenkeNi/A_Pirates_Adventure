#pragma once
#include <../Scene/Scene.h>


// Derive MainMenuScene from MenuScene??
class MenuScene : public Hi_Engine::Scene
{
public:
	//MenuScene(Hi_Engine::ECSCoordinator& ecs);
	//~MenuScene();

	void OnUpdate(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};