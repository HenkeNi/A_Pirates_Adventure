#pragma once
#include "../Scene.h"


// Derive MainMenuScene from MenuScene??
class MenuScene : public Scene
{
public:
	MenuScene(SharedContext aContext);
	~MenuScene();

	void Update(float aDeltaTime)			  override;
	void LateUpdate(float aDeltaTime)		  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};