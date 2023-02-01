#pragma once
#include "../Scene.h"


class GameScene : public Scene
{
public:
	GameScene(SceneManagerProxy aProxy);
	~GameScene();

	void Update(float aDeltaTime)			  override;
	void LateUpdate(float aDeltaTime)		  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;


private:
	// GameWorld class?? -> Contains a current map??
};

