#pragma once
#include <../Scene/Scene.h>


class LoadingScene : public Hi_Engine::Scene
{
public:
	//LoadingScene(Hi_Engine::ECSCoordinator& ecs);
	//~LoadingScene();

	void OnUpdate(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};

