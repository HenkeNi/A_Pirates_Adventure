#pragma once
#include "../Scene.h"


class TitleScene : public Scene 
{
public:
	TitleScene(SharedContext context);
	~TitleScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};