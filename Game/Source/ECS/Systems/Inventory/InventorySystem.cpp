#include "Pch.h"
#include "InventorySystem.h"
#include "Entities/EntityManager.h"
#include "Components/Combat/CombatComponents.h"
#include "Components/Controllers/ControllerComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"


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

	auto pickups = m_entityManager->FindAll<PickupColliderComponent>();
	auto players = m_entityManager->FindAll<PlayerControllerComponent>();		// ADD FindOne or just Find()??

	if (players.empty() || !players[0])
		return;

	auto playerTransform = players[0]->GetComponent<TransformComponent>();

	std::vector<Entity*> entitiesToRemove;

	for (auto pickup : pickups)
	{
		// either check the distance or if colliding..

		auto pickupTransform = pickup->GetComponent<TransformComponent>();

		float distance = pickupTransform->CurrentPos.DistanceTo(playerTransform->CurrentPos);
		if (distance < 0.5f)
		{
			auto inventoryComponent = players[0]->GetComponent<InventoryComponent>();

			unsigned currentValue = 0;

			auto itr = inventoryComponent->Inventory.find("log");
			if (itr != inventoryComponent->Inventory.end())
			{
				currentValue = itr->second;
			}

			// TODO; fetch resource type from ResourceComponent	
			inventoryComponent->Inventory.insert_or_assign("log", currentValue + 1);

			std::cout << "added resource to inventory!: " << currentValue + 1 << " logs!\n";
			entitiesToRemove.push_back(pickup);
		}
	}

	for (auto* entity : entitiesToRemove)
		m_entityManager->Destroy(entity->GetID());
}