#pragma once
#include "../../Scene.h"


class DungeonScene : public Scene
{
public:
	DungeonScene(SharedContext aContext);
	~DungeonScene();

	void Update(float aDeltaTime)			  override;
	void LateUpdate(float aDeltaTime)		  override;
	void Draw()							const override;

	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;

private:
};

