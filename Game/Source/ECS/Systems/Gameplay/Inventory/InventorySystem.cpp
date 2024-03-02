#include "Pch.h"
#include "InventorySystem.h"
#include "Entities/EntityManager.h"
#include "Components/AI/AIComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"


InventorySystem::InventorySystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntitiesCollided, this);
}

InventorySystem::~InventorySystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntitiesCollided, this);
}

void InventorySystem::Receive(Message& aMsg)
{
	int xx = 10;
	xx += 10;
	// listen to entity collision => make sure its done after equipment system
}
  
void InventorySystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	return; // listen to collision event instead?

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