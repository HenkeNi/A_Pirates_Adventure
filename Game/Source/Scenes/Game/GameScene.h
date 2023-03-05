#pragma once
#include "../Scene.h"
#include "../World/GameWorld.h"

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
	GameWorld	m_world;
	// GameWorld class?? -> Contains a current map??
};

