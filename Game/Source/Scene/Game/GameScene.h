#pragma once
#include "../Scene.h"
#include "../SceneManager.h"
//#include "../World/GameWorld.h"
#include "../World/Map/Map.h"


class GameScene : public Scene
{
public:
	GameScene(SharedContext aContext);
	~GameScene();

	void Update(float aDeltaTime)			  override;
	void LateUpdate(float aDeltaTime)		  override;
	void Draw()							const override;

	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;


private:
	SceneManager m_sceneManager;	// will contain WorldScene and IndoorScene... (amongst others)...


		// TEST
	Map m_map;

	//GameWorld	m_world; // GameWorld class?? -> Contains a current map??w
	// SceneManager?? Contains OverworldScene, CaveScene, etc..??
};

