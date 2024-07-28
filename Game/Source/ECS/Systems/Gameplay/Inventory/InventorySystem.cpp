#include "Pch.h"
#include "InventorySystem.h"
#include "ECS.h"
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

	auto entities = std::any_cast<std::vector<Entity>>(message.GetData());

	Entity player;
	Entity collectable;

	InventoryComponent* inventoryComponent = nullptr;
	CollectableComponent* collectableComponent = nullptr;

	// assure entities are an equippable item and an actor with equipment
	for (auto& entity : entities)
	{
		if (m_ecs->HasComponent<InventoryComponent>(entity))
			player = entity;
		else if (m_ecs->HasComponent<CollectableComponent>(entity))
			collectable = entity;
	}

	if (!inventoryComponent || !collectableComponent)
		return;

	// use function to check for relevant components??
	if (!CanPickup(collectable))
		return;

	// TODO: make sure dont send event each fraem!
	if (CollectItem(player, collectable))
	{
		auto* collectableComponent = m_ecs->GetComponent<CollectableComponent>(collectable);
		collectableComponent->IsCollected = true;
		// m_entityManager->Destroy(collectable->GetID()); -- do in a clean up system?
		message.HandleMessage(); // rename MarkAsHandled(); ??

		PostMaster::GetInstance().SendMessage({ eMessage::ItemCollected, collectable });
	}
}
  
void InventorySystem::Update(float deltaTime)
{
	assert(m_ecs && "ERROR: ECS is nullptr!");

	// Clean up collected items
	std::vector<Entity> collectedEntities;

	auto entities = m_ecs->FindEntities(m_signatures["Collectables"]);
	for (auto entity : entities)
	{
		auto* collectableComponent = m_ecs->GetComponent<CollectableComponent>(entity);
		if (collectableComponent->IsCollected)
			collectedEntities.push_back(entity);
	}

	for (const auto& entity : collectedEntities)
		m_ecs->DestroyEntity(entity);
}

void InventorySystem::SetSignature()
{
	m_signatures.insert({ "Collectables", m_ecs->GetSignature<CollectableComponent>() });
}

bool InventorySystem::CanPickup(Entity entity)
{
	if (auto* collectableComponent = m_ecs->GetComponent<CollectableComponent>(entity))
	{
		double currentTime = Hi_Engine::Engine::GetTimer().GetTotalTime();
		double endTime = collectableComponent->SpawnTimestamp + collectableComponent->PickupDelay;
		return endTime < currentTime;
	}

	return false;
}

bool InventorySystem::CollectItem(Entity owner, Entity item)
{
	auto* inventoryComponent = m_ecs->GetComponent<InventoryComponent>(owner);
	auto* collectableComponent = m_ecs->GetComponent<CollectableComponent>(item);

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
