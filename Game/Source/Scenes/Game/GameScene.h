#pragma once
#include "../Scene.h"
#include "../SceneManager.h"
#include "../Map/Map.h"


class GameScene : public Scene
{
public:
	GameScene(SharedContext aContext);
	~GameScene();

	void Register(ScenePtr_t aScene, eScene aType);

	void Update(float aDeltaTime)			  override;
	void LateUpdate(float aDeltaTime)		  override;
	void Draw()							const override;

	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;


private:
	SceneManager	m_sceneManager;	// will contain WorldScene and IndoorScene... (amongst others)...
	// Map				m_map;
};