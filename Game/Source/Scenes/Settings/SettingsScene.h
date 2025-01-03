#pragma once
#include "../Scene.h"


class SettingsScene : public Scene
{
public:
	//SettingsScene(Hi_Engine::ECSCoordinator& ecs);
	//~SettingsScene();

	void Update(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};