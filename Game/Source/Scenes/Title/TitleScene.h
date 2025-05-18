#pragma once
#include <../Scene/Scene.h>


class TitleScene : public Hi_Engine::Scene
{
public:
	//TitleScene(Hi_Engine::ECSCoordinator& ecs);
	//~TitleScene();

	void OnUpdate(float deltaTime)		  override;
	void OnEnter()						  override;
	void OnExit()						  override;
};