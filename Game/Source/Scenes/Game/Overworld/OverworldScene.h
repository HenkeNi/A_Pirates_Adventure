#pragma once
#include <../Scene/Scene.h>


class OverworldScene : public Hi_Engine::Scene
{
public:
	//OverworldScene(Hi_Engine::ECSCoordinator& ecs);
	//~OverworldScene();

	void OnUpdate(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};