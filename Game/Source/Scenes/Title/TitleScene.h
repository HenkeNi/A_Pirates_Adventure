#pragma once
#include "../Scene.h"


class TitleScene : public Scene 
{
public:
	TitleScene(ECS& ecs);
	~TitleScene();

	void Update(float deltaTime)			  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};