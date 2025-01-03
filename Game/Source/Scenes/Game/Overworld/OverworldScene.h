#pragma once
#include "../../Scene.h"


class OverworldScene : public Scene
{
public:
	//OverworldScene(Hi_Engine::ECSCoordinator& ecs);
	//~OverworldScene();

	void Update(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};