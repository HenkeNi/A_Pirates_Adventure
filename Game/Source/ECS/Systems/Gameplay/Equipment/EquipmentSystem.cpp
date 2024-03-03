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

void EquipmentSystem::Receive(Message& aMsg)
{
	if (aMsg.GetMessageType() != eMessage::EntitiesCollided) // TODO: called each frame!
		return;

	auto entities = std::any_cast<std::vector<Entity*>>(aMsg.GetData()); // Dont pass colliding entities?
	
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
		aMsg.HandleMessage(); // rename MarkAsHandled(); ??

	// sword, etc should have a pickup component?!
	// if item was equiped...  or colliding with item (an not such slot is taken)
}

void EquipmentSystem::Update(float aDeltaTime)
{
}

bool EquipmentSystem::EquipItem(class Entity* anOwner, class Entity* anItem)
{
	if (!anOwner || !anItem)
		return false;

	auto* equippableComponent = anItem->GetComponent<EquippableComponent>();
	if (equippableComponent->IsEquipped)
		return false;

	equippableComponent->IsEquipped = true;
	// remove equippable compoentn??

	auto* equipmentComponent = anOwner->GetComponent<EquipmentComponent>();
	equipmentComponent->EquippedItemIDs[(int)eEquipmentSlot::Melee] = anItem->GetID();
	
	
	auto childEntities = anOwner->GetComponent<SubEntitiesComponent>();
	childEntities->IDs.push_back(anItem->GetID());

	return true;


	// TODO; Check if equippable slot is available... and assing to right slot
	// TODO; destroy entity when equipping it?

}