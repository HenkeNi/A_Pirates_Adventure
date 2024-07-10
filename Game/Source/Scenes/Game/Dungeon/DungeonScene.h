#pragma once
#include "../../Scene.h"


class DungeonScene : public Scene
{
public:
	DungeonScene(ECS& ecs);
	~DungeonScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};

