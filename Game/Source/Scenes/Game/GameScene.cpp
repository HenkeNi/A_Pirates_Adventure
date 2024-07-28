#include "Pch.h"
#include "GameScene.h"
#include "SceneTypes.h"
#include "Dungeon/DungeonScene.h"
#include "Overworld/OverworldScene.h"
#include "Inventory/InventoryScene.h"


GameScene::GameScene(ECS& ecs)
	: Scene{ ecs }
{
}

GameScene::~GameScene()
{
}

void GameScene::Update(float deltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->Update(deltaTime);
	}
}

void GameScene::LateUpdate(float deltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->LateUpdate(deltaTime);
	}
}

void GameScene::Draw() const
{
	std::weak_ptr<const Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->Draw();
	}
}

void GameScene::OnCreated()
{
	// TODO; pass the Game Scene's entitymanager to subscene's?

	m_sceneManager.Register<OverworldScene>(eScene::Overworld, m_ecs);
	m_sceneManager.Register<DungeonScene>(eScene::Dungeon, m_ecs);
	m_sceneManager.Register<InventoryScene>(eScene::Inventory, m_ecs);

	// m_sceneManager.Init({ eScene::Overworld });
}

void GameScene::OnEnter()
{
	PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, eScene::Overworld });

	/*std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->OnEnter();
	}*/
}

void GameScene::OnExit()
{
}