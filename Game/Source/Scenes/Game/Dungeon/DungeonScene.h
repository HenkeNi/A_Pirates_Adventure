#pragma once
#include "../../Scene.h"


class DungeonScene : public Scene
{
public:
	//DungeonScene(Hi_Engine::ECSCoordinator& ecs);
	//~DungeonScene();

	void Update(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};

