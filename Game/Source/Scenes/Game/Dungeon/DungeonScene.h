#pragma once
#include "../../Scene.h"


class DungeonScene : public Scene
{
public:
	DungeonScene(SharedContext context);
	~DungeonScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;

private:
};

