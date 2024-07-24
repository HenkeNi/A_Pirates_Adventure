#pragma once
#include "../Scene.h"


// Derive MainMenuScene from MenuScene??
class MenuScene : public Scene
{
public:
	MenuScene(ECS& ecs);
	~MenuScene();

	void Update(float deltaTime)			  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};