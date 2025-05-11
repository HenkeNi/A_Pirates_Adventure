#pragma once
#include <../Scene/Scene.h>


class SettingsScene : public Hi_Engine::Scene
{
public:
	//SettingsScene(Hi_Engine::ECSCoordinator& ecs);
	//~SettingsScene();

	void Update(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};