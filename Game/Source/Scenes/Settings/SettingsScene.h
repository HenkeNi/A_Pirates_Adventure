#pragma once
#include "../Scene.h"


class SettingsScene : public Scene
{
public:
	SettingsScene(ECS& ecs);
	~SettingsScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};