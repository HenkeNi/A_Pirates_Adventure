#include "Pch.h"
#include "EquipmentSystem.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"


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

	auto entities = std::any_cast<std::vector<Entity>>(message.GetData()); // Dont pass colliding entities?
	
	EquipmentComponent* equipmentComponent = nullptr;
	EquippableComponent* equippableComponent = nullptr;
	
	Entity item = -1;
	Entity owner = -1;

	// assure entities are an equippable item and an actor with equipment
	for (auto& entity : entities)
	{
		if (auto* component = m_ecs->GetComponent<EquipmentComponent>(entity))
		{
			equipmentComponent ;
			owner = entity;
		}
		else if (auto* component = m_ecs->GetComponent<EquippableComponent>(entity))
		{
			item = entity;
			equippableComponent = component;
		}
	}

	if (!equipmentComponent || !equippableComponent || equippableComponent->IsEquipped)
		return;
	
	// TODO: make sure dont send event each fraem!
	//if (EquipItem(player, equippable))
	{
		equippableComponent->IsEquipped = true;
		// remove equippable compoentn??

		equipmentComponent->EquippedItemIDs[(int)eEquipmentSlot::Melee] = item;

		auto* subEntitiesComponent = m_ecs->GetComponent<SubEntitiesComponent>(owner);
		subEntitiesComponent->IDs.push_back(item);

		m_ecs->RemoveComponent<CollectableComponent>(item);

		message.HandleMessage(); // rename MarkAsHandled(); ??
		PostMaster::GetInstance().SendMessage({ eMessage::ItemCollected, item });
	}

	// sword, etc should have a pickup component?!
	// if item was equiped...  or colliding with item (an not such slot is taken)
}

void EquipmentSystem::Update(float deltaTime)
{
}

void EquipmentSystem::SetSignature()
{
}

bool EquipmentSystem::EquipItem(Entity owner, Entity item)
{
	//if (!owner || !item)
	//	return false;

	//auto* equippableComponent = item->GetComponent<EquippableComponent>();
	//if (equippableComponent->IsEquipped)
	//	return false;

	//equippableComponent->IsEquipped = true;
	//// remove equippable compoentn??

	//auto* equipmentComponent = owner->GetComponent<EquipmentComponent>();
	//equipmentComponent->EquippedItemIDs[(int)eEquipmentSlot::Melee] = item->GetID();
	//
	//
	//auto childEntities = owner->GetComponent<SubEntitiesComponent>();
	//childEntities->IDs.push_back(item->GetID());

	//item->RemoveComponent<CollectableComponent>(); // Maybe?

	return true;


	// TODO; Check if equippable slot is available... and assing to right slot
	// TODO; destroy entity when equipping it?

}