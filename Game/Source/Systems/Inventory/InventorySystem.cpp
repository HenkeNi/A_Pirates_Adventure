#include "Pch.h"
#include "InventorySystem.h"
#include "EntityManager.h"
#include "Combat/CombatComponents.h"
#include "Controllers/ControllerComponents.h"
#include "Core/CoreComponents.h"
#include "Inventory/InventoryComponents.h"


InventorySystem::InventorySystem()
{
}

InventorySystem::~InventorySystem()
{
}

void InventorySystem::Receive(Message& aMsg)
{
}
  
void InventorySystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	auto pickups = m_entityManager->FindAllWithComponents<PickupColliderComponent>();
	auto* player = m_entityManager->FindAllWithComponents<PlayerControllerComponent>()[0];		// ADD FindOne or just Find()??

	auto playerTransform = player->GetComponent<TransformComponent>();

	std::vector<Entity*> entitiesToRemove;

	for (auto pickup : pickups)
	{
		// either check the distance or if colliding..

		auto pickupTransform = pickup->GetComponent<TransformComponent>();

		float distance = pickupTransform->m_currentPos.DistanceTo(playerTransform->m_currentPos);
		if (distance < 0.5f)
		{
			auto inventoryComponent = player->GetComponent<InventoryComponent>();

			unsigned currentValue = 0;

			auto itr = inventoryComponent->m_inventory.find("log");
			if (itr != inventoryComponent->m_inventory.end())
			{
				currentValue = itr->second;
			}

			// TODO; fetch resource type from ResourceComponent	
			inventoryComponent->m_inventory.insert_or_assign("log", currentValue + 1);

			std::cout << "added resource to inventory!: " << currentValue + 1 << " logs!\n";
			entitiesToRemove.push_back(pickup);
		}
	}

	for (auto* entity : entitiesToRemove)
		m_entityManager->Destroy(entity->GetID());
}