#pragma once
#include "../Scene.h"


class TitleScene : public Scene 
{
public:
	//TitleScene(Hi_Engine::ECSCoordinator& ecs);
	//~TitleScene();

	void Update(float deltaTime)		  override;
	void OnEnter()						  override;
	void OnExit()						  override;
};