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

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 16; ++col)
		{
			auto* box = m_entityManager.Create("inventory_slot");
			box->GetComponent<TransformComponent>()->CurrentPos = { (float)col, (float)row };
		}
	}
	//auto* box = m_entityManager.Create("inventory_slot");
	//box->GetComponent<TransformComponent>()->CurrentPos = { 20.f, 20.f };


	//auto* box1 = m_entityManager.Create("inventory_slot");
	//box1->GetComponent<TransformComponent>()->CurrentPos = { 120.f, 120.f };

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
