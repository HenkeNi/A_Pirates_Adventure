#pragma once
#include "../../Scene.h"


class OverworldScene : public Scene
{
public:
	OverworldScene(ECS& ecs);
	~OverworldScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};