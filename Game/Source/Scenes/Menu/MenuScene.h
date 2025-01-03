#pragma once
#include "../Scene.h"


// Derive MainMenuScene from MenuScene??
class MenuScene : public Scene
{
public:
	//MenuScene(Hi_Engine::ECSCoordinator& ecs);
	//~MenuScene();

	void Update(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};