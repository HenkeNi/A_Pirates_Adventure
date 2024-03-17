#include "Pch.h"
#include "EquipmentSystem.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"


EquipmentSystem::EquipmentSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntitiesCollided, this);
}

EquipmentSystem::~EquipmentSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntitiesCollided, this);
}

void EquipmentSystem::Receive(Message& message)
{
	if (message.GetMessageType() != eMessage::EntitiesCollided) // TODO: called each frame!
		return;

	auto entities = std::any_cast<std::vector<Entity*>>(message.GetData()); // Dont pass colliding entities?
	
	Entity* player = nullptr;
	Entity* equippable = nullptr;
	
	// assure entities are an equippable item and an actor with equipment
	for (auto& entity : entities)
	{
		if (entity->HasComponent<EquipmentComponent>())
			player = entity;
		else if (entity->HasComponent<EquippableComponent>())
			equippable = entity;
	}

	if (!player || !equippable)
		return;
	
	// TODO: make sure dont send event each fraem!
	if (EquipItem(player, equippable))
		message.HandleMessage(); // rename MarkAsHandled(); ??

	// sword, etc should have a pickup component?!
	// if item was equiped...  or colliding with item (an not such slot is taken)
}

void EquipmentSystem::Update(float deltaTime)
{
}

bool EquipmentSystem::EquipItem(class Entity* owner, class Entity* item)
{
	if (!owner || !item)
		return false;

	auto* equippableComponent = item->GetComponent<EquippableComponent>();
	if (equippableComponent->IsEquipped)
		return false;

	equippableComponent->IsEquipped = true;
	// remove equippable compoentn??

	auto* equipmentComponent = owner->GetComponent<EquipmentComponent>();
	equipmentComponent->EquippedItemIDs[(int)eEquipmentSlot::Melee] = item->GetID();
	
	
	auto childEntities = owner->GetComponent<SubEntitiesComponent>();
	childEntities->IDs.push_back(item->GetID());

	item->RemoveComponent<CollectableComponent>(); // Maybe?

	return true;


	// TODO; Check if equippable slot is available... and assing to right slot
	// TODO; destroy entity when equipping it?

}