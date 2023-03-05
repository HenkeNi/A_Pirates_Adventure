#pragma once
#include "../Scene.h"


class TitleScene : public Scene
{
public:
	TitleScene(SceneManagerProxy aProxy);
	~TitleScene();

	void			Update(float aDeltaTime)			  override;
	void			LateUpdate(float aDeltaTime)		  override;
	void			Draw()							const override;

	void			OnCreated()							  override;
	void			OnEnter()							  override;
	void			OnExit()							  override;

private:
	float			m_duration;
	//float			m_duration, m_elapsedTime; // register a time callback in a time manager isntead?!
};