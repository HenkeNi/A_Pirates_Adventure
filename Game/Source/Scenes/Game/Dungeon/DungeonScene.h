#pragma once
#include <../Scene/Scene.h>


class DungeonScene : public Hi_Engine::Scene
{
public:
	//DungeonScene(Hi_Engine::ECSCoordinator& ecs);
	//~DungeonScene();

	void OnUpdate(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};

