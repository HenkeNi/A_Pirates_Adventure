#pragma once
#include "../Scene.h"


class MenuScene : public Scene
{
public:
	MenuScene(SceneManagerProxy aProxy);
	~MenuScene();

	void			Update(float aDeltaTime)			  override;
	void			LateUpdate(float aDeltaTime)		  override;
	void			Draw()							const override;

	void			OnEnter()							  override;
	void			OnExit()							  override;
};

