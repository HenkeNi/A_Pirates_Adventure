#pragma once
#include "../Scene.h"


class LoadingScene : public Scene
{
public:
	LoadingScene(SceneManagerProxy aProxy);
	~LoadingScene();

	void			Init(rapidjson::Value& aValue)		  override;
	void			Update(float aDeltaTime)			  override;
	void			LateUpdate(float aDeltaTime)		  override;
	void			Draw()							const override;

	void			OnEnter()							  override;
	void			OnExit()							  override;
};

