#include "Pch.h"
#include "InventoryScene.h"

//
//InventoryScene::InventoryScene(Hi_Engine::ECSCoordinator& ecs)
//	: Scene{ ecs }
//{
//}
//
//InventoryScene::~InventoryScene()
//{
//}

void InventoryScene::OnUpdate(float deltaTime)
{

}

void InventoryScene::OnEnter()
{
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 16; ++col)
		{
			//auto* box = m_ecs.GetEntityManager().Create("inventory_slot");
			//box->GetComponent<TransformComponent>()->CurrentPos = { (float)col, (float)row };
			//box->GetComponent<TransformComponent>()->CurrentPos = { (float) * 0.01f, (float)row * 0.01f };
			//box->GetComponent<TransformComponent>()->CurrentPos = { 0.1f, 0.1f };
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
	// m_ecs.DestroyAllEntities();
}
