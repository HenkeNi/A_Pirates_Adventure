#pragma once
#include "../../Scene.h"

class OverworldScene : public Scene
{
public:
	OverworldScene(SharedContext context);
	~OverworldScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;

private:
};