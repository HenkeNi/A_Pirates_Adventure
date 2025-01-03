#pragma once
#include "../Scene.h"


class LoadingScene : public Scene
{
public:
	//LoadingScene(Hi_Engine::ECSCoordinator& ecs);
	//~LoadingScene();

	void Update(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};

