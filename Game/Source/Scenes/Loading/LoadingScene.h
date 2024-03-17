#pragma once
#include "../Scene.h"


class LoadingScene : public Scene
{
public:
	LoadingScene(SharedContext context);
	~LoadingScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};

