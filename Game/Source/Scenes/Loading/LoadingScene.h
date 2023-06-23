#pragma once
#include "../Scene.h"


class LoadingScene : public Scene
{
public:
	LoadingScene(SharedContext aContext);
	~LoadingScene();

	void Update(float aDeltaTime)			  override;
	void LateUpdate(float aDeltaTime)		  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};

