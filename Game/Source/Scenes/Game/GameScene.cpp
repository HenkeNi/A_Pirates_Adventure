#include "Pch.h"
#include "GameScene.h"
//#include "SceneTypes.h"
#include "Dungeon/DungeonScene.h"
#include "Overworld/OverworldScene.h"
#include "Inventory/InventoryScene.h"


//GameScene::GameScene(Hi_Engine::ECSCoordinator& ecs)
//	: Scene{ ecs }
//{
//}
//
//GameScene::~GameScene()
//{
//}

void GameScene::OnUpdate(float deltaTime)
{
	//std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	/*if (auto scene = activeScene.lock())
	{
		scene->Update(deltaTime);
	}*/
}

void GameScene::OnCreated()
{
	// TODO; pass the Game Scene's entitymanager to subscene's?

	//m_sceneManager.Register<OverworldScene>(eScene::Overworld);
	//m_sceneManager.Register<DungeonScene>(eScene::Dungeon);
	//m_sceneManager.Register<InventoryScene>(eScene::Inventory);

	// m_sceneManager.Init({ eScene::Overworld });
}

void GameScene::OnEnter()
{
	// PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, eScene::Overworld });

	/*std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->OnEnter();
	}*/
}

void GameScene::OnExit()
{
}