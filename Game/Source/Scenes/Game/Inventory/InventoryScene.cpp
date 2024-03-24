#include "Pch.h"
#include "InventoryScene.h"
#include "Systems/SystemManager.h"

InventoryScene::InventoryScene(SharedContext context)
	: Scene{ context }
{
}

InventoryScene::~InventoryScene()
{
}

void InventoryScene::Update(float deltaTime)
{
	m_sharedContext.SystemManager.Update(deltaTime);
}

void InventoryScene::LateUpdate(float deltaTime)
{
}

void InventoryScene::Draw() const
{
	m_sharedContext.SystemManager.Draw();
}

void InventoryScene::OnCreated()
{
}

void InventoryScene::OnEnter()
{
	auto& systemManager = m_sharedContext.SystemManager;
	systemManager.Init(&m_entityManager);

	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");

	// UI element box...
	// render slots in grid...
	// todo. drag and drop

	// player stats
	// see player character
		// equip different items...
}

void InventoryScene::OnExit()
{
	m_entityManager.DestroyAll();
}
