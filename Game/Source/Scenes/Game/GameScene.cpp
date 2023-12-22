#include "Pch.h"
#include "GameScene.h"
#include "Systems/SystemManager.h"
#include "Dungeon/DungeonScene.h"
#include "Overworld/OverworldScene.h"


GameScene::GameScene(SharedContext aContext)
	: Scene{ aContext }
{
}

GameScene::~GameScene()
{
}

//void GameScene::Register(MutableScene aScene, eScene aType)
//{
//	m_sceneManager.Register(std::move(aScene), aType);
//}

void GameScene::Update(float aDeltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->Update(aDeltaTime);
	}

	//m_sceneManager.Update(aDeltaTime); // not needed??
}

void GameScene::LateUpdate(float aDeltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->LateUpdate(aDeltaTime);
	}


	//m_sceneManager.LateUpdate(aDeltaTime); // not needed??
}

void GameScene::Draw() const
{
	std::weak_ptr<const Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->Draw();
	}

	//m_sceneManager.Draw(); // not needed??
}

void GameScene::OnCreated()
{
	m_sceneManager.Register(std::make_unique<OverworldScene>(m_sharedContext),	eScene::Overworld);
	m_sceneManager.Register(std::make_unique<DungeonScene>(m_sharedContext),	eScene::Dungeon);

	//m_sceneManager.Init((int)eScene::Overworld);
	std::bitset<(int)eScene::Count> scenes(0);
	scenes[(int)eScene::Overworld] = 1;
	m_sceneManager.Init(scenes);

	// m_sceneManager.Init((int)eScene::Overworld); // TODO; FIX!
}

void GameScene::OnEnter()
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->OnEnter();
	}

	// m_sceneManager.GetActiveScene().OnEnter();
	// HOW TO CALL OnEnter on SCENE!
	// 
	// 
	// 	
	// TODO; on ENter...


	// How to call on enter for active subscene
}

void GameScene::OnExit()
{
}