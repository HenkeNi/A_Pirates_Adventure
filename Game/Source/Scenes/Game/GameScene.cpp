#include "Pch.h"
#include "GameScene.h"
//#include "SceneTypes.h"
#include "Dungeon/DungeonScene.h"
#include "Overworld/OverworldScene.h"
#include "Inventory/InventoryScene.h"


GameScene::GameScene(Hi_Engine::ServiceRegistry& registry)
	: Scene{ registry }
{
}

void GameScene::OnUpdate(float deltaTime)
{
	auto activeScene = m_subSceneManager.GetActive();

	if (auto scene = activeScene.lock())
	{
		scene->Update(deltaTime);
	}
}

void GameScene::OnCreated()
{
	m_subSceneManager.Emplace<OverworldScene>(m_serviceRegistry);
	//m_subSceneManager.Emplace<DungeonScene>(m_serviceRegistry);
}

void GameScene::OnEnter()
{
	m_subSceneManager.SetActive<OverworldScene>(); // not here? or set active on creted... and the use TransitionTO here??
	
	auto scene = m_subSceneManager.GetActive();
	scene.lock()->OnEnter();

	
	// PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, eScene::Overworld });

	/*
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();

	if (auto scene = activeScene.lock())
	{
		scene->OnEnter();
	}
	*/
}

void GameScene::OnExit()
{
}