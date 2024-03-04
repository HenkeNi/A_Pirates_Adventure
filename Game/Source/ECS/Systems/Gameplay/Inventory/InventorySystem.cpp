#include "Pch.h"
#include "InventorySystem.h"
#include "Entities/EntityManager.h"
#include "Components/AI/AIComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"


InventorySystem::InventorySystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntitiesCollided, this); // Listen to trigger instead??
}

InventorySystem::~InventorySystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntitiesCollided, this);
}

void InventorySystem::Receive(Message& aMsg)
{
	// Listen for collision events (triggers)?
	// listen to entity collision => make sure its done after equipment system

	auto entities = std::any_cast<std::vector<Entity*>>(aMsg.GetData());

	Entity* player = nullptr;
	Entity* collectable = nullptr;

	// assure entities are an equippable item and an actor with equipment
	for (auto& entity : entities)
	{
		if (entity->HasComponent<InventoryComponent>())
			player = entity;
		else if (entity->HasComponent<CollectableComponent>())
			collectable = entity;
	}

	if (!player || !collectable)
		return;

	// TODO: make sure dont send event each fraem!
	if (CollectItem(player, collectable))
	{
		auto* collectableComponent = collectable->GetComponent<CollectableComponent>();
		collectableComponent->IsCollected = true;
		// m_entityManager->Destroy(collectable->GetID()); -- do in a clean up system?
		aMsg.HandleMessage(); // rename MarkAsHandled(); ??
	}
}
  
void InventorySystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	std::vector<unsigned> collectedEntityIDs;

	auto entities = m_entityManager->FindAll<CollectableComponent>();
	for (const auto& entity : entities)
	{
		auto* collectableComponent = entity->GetComponent<CollectableComponent>();
		if (collectableComponent->IsCollected)
			collectedEntityIDs.push_back(entity->GetID());
	}

	for (const auto& entity : collectedEntityIDs)
		m_entityManager->Destroy(entity);
}

bool InventorySystem::CollectItem(class Entity* anOwner, class Entity* anItem)
{
	if (!anOwner || !anItem)
		return false;

	auto* inventoryComponent = anOwner->GetComponent<InventoryComponent>();
	auto* collectableComponent = anItem->GetComponent<CollectableComponent>();

	auto& slots = inventoryComponent->Slots;
	auto itr = std::find_if(slots.begin(), slots.end(), [=](const InventorySlot& aSlot) { return aSlot.Item.ItemID == collectableComponent->Item.ItemID; });
	
	// Item was already found in inventory...
	if (itr != slots.end())
	{
		if (itr->Quantity < itr->Item.MaxStack)
		{
			++itr->Quantity; 
			return true;
		}
	}
	
	// If inventory contains an empty space
	for (int i = 0; i < inventoryComponent->UnlockedSlots; ++i)
	{
		if (slots[i].Item.ItemID == "Empty")
		{
			slots[i].Item = collectableComponent->Item;
			return true;
		}
	}
	
	return false;
}
