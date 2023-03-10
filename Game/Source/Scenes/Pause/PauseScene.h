#pragma once
#include "../Scene.h"

// Derive PauseSceen from MenuScene??
class PauseScene : public Scene
{
public:
	PauseScene(SceneManagerProxy aProxy);
	~PauseScene();

	void			Update(float aDeltaTime)			  override;
	void			LateUpdate(float aDeltaTime)		  override;
	void			Draw()							const override;

	void			OnCreated()							  override;
	void			OnEnter()							  override;
	void			OnExit()							  override;


private:
	std::vector<std::function<void()>> m_callbacks; // TODO: find other way??
};

