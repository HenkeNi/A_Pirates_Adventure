#pragma once
#include "../Scene.h"


// Derive MainMenuScene from MenuScene??
class MenuScene : public Scene
{
public:
	MenuScene(SharedContext context);
	~MenuScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};