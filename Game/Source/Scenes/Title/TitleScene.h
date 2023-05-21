#pragma once
#include "../Scene.h"


class TitleScene : public Scene 
{
public:
	TitleScene(SceneManagerProxy aProxy);
	~TitleScene();

	void			Init(rapidjson::Value& aValue)		  override; 
	void			Update(float aDeltaTime)			  override;
	void			LateUpdate(float aDeltaTime)		  override;
	void			Draw()							const override;

	void			OnCreated()							  override;
	void			OnEnter()							  override;
	void			OnExit()							  override;
};