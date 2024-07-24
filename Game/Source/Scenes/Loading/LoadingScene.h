#pragma once
#include "../Scene.h"


class LoadingScene : public Scene
{
public:
	LoadingScene(ECS& ecs);
	~LoadingScene();

	void Update(float deltaTime)			  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};

