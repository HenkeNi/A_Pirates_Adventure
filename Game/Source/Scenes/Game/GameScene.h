#pragma once
#include "../Scene.h"
#include "../SceneManager.h"


class GameScene : public Scene
{
public:
	GameScene(ECS& ecs);
	~GameScene();

	//void Register(MutableScene aScene, eScene aType);

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnCreate()							  override;
	void OnEnter()							  override;
	void OnExit()							  override;

private:
	SceneManager	m_sceneManager;	// will contain WorldScene and IndoorScene... (amongst others)...
};