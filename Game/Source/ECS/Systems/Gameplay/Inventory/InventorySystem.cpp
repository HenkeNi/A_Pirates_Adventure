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

void InventorySystem::Receive(Message& message)
{
	// Listen for collision events (triggers)?
	// listen to entity collision => make sure its done after equipment system

	auto entities = std::any_cast<std::vector<Entity*>>(message.GetData());

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


	// use function to check for relevant components??
	if (!CanPickup(collectable))
		return;

	// TODO: make sure dont send event each fraem!
	if (CollectItem(player, collectable))
	{
		auto* collectableComponent = collectable->GetComponent<CollectableComponent>();
		collectableComponent->IsCollected = true;
		// m_entityManager->Destroy(collectable->GetID()); -- do in a clean up system?
		message.HandleMessage(); // rename MarkAsHandled(); ??
	}
}
  
void InventorySystem::Update(float deltaTime)
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

bool InventorySystem::CanPickup(Entity* entity)
{
	if (auto* collectableComponent = entity->GetComponent<CollectableComponent>())
	{
		double currentTime = Hi_Engine::Engine::GetTimer().GetTotalTime();
		double endTime = collectableComponent->SpawnTimestamp + collectableComponent->PickupDelay;
		return endTime < currentTime;
	}

	return false;
}

bool InventorySystem::CollectItem(class Entity* owner, class Entity* item)
{
	if (!owner || !item)
		return false;

	auto* inventoryComponent = owner->GetComponent<InventoryComponent>();
	auto* collectableComponent = item->GetComponent<CollectableComponent>();

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
	for (unsigned i = 0; i < inventoryComponent->UnlockedSlots; ++i)
	{
		if (slots[i].Item.ItemID == "Empty")
		{
			slots[i].Item = collectableComponent->Item;
			return true;
		}
	}
	
	return false;
}
