#pragma once
#include "../Scene.h"
#include "../World/GameWorld.h"
#include "../World/Map/Map.h"

class GameScene : public Scene
{
public:
	GameScene(SceneManagerProxy aProxy);
	~GameScene();

	void Init(rapidjson::Value& aValue)  	  override;
	void Update(float aDeltaTime)			  override;
	void LateUpdate(float aDeltaTime)		  override;
	void Draw()							const override;

	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;


private:
	// put a scene manager here??

		// TEST
	Map m_map;

	//GameWorld	m_world; // GameWorld class?? -> Contains a current map??w
	// SceneManager?? Contains OverworldScene, CaveScene, etc..??
};

