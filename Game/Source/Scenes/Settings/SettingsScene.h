#pragma once
#include "../Scene.h"


class SettingsScene : public Scene
{
public:
	SettingsScene(SharedContext context);
	~SettingsScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};