#include "Pch.h"
#include "GameScene.h"
#include "Systems/SystemManager.h"
#include "Dungeon/DungeonScene.h"
#include "Overworld/OverworldScene.h"
#include "Inventory/InventoryScene.h"


GameScene::GameScene(SharedContext context)
	: Scene{ context }
{
}

GameScene::~GameScene()
{
}

//void GameScene::Register(MutableScene aScene, eScene aType)
//{
//	m_sceneManager.Register(std::move(aScene), aType);
//}

void GameScene::Update(float deltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->Update(deltaTime);
	}

	// TODO: should update own systems (in shared context)??
}

void GameScene::LateUpdate(float deltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->LateUpdate(deltaTime);
	}

	// TODO: should update own systems (in shared context)??
}

void GameScene::Draw() const
{
	std::weak_ptr<const Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->Draw();
	}

	// TODO: should update own systems (in shared context)??
}

void GameScene::OnCreated()
{
	// TODO; pass the Game Scene's entitymanager to subscene's?

	m_sceneManager.Register<OverworldScene>(eScene::Overworld, m_sharedContext);
	m_sceneManager.Register<DungeonScene>(eScene::Dungeon, m_sharedContext);
	m_sceneManager.Register<InventoryScene>(eScene::Inventory, m_sharedContext);

	m_sceneManager.Init({ eScene::Overworld });
}

void GameScene::OnEnter()
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->OnEnter();
	}
}

void GameScene::OnExit()
{
}