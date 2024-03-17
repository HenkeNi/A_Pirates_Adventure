#pragma once
#include "../Scene.h"

// Derive PauseSceen from MenuScene??
class PauseScene : public Scene
{
public:
	PauseScene(SharedContext context);
	~PauseScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};