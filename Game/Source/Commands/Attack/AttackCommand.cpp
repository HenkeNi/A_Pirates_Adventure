#include "Pch.h"
#include "AttackCommand.h"
#include "Entities/Entity.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Components/Core/CoreComponents.h"


AttackCommand::AttackCommand()
{
}

void AttackCommand::Execute(Entity* entity)
{
	if (!entity)
		return;

	if (auto* characterStateComponent = entity->GetComponent<CharacterStateComponent>())
	{
		characterStateComponent->IsAttacking = true;
	}

	//// get equipped weapon instead..
	//if (auto* equipmentComponent = entity->GetComponent<EquipmentComponent>())
	//{
	//	int weaponID = equipmentComponent->EquippedItemIDs[(int)eEquipmentSlot::Melee];
	//	// fetch weapon from entitymanager?!
	//}
	//
	//if (auto* attackComponent = entity->GetComponent<AttackComponent>())
	//{
	//	attackComponent->IsEnabled = true;
	//}

	// send event?
}

// Not called...
bool AttackCommand::CanPerform(Entity* entity) const
{
	if (!entity)
		return false;

	if (auto* equipmentComponent = entity->GetComponent<EquipmentComponent>())
	{
		auto equipment = equipmentComponent->EquippedItemIDs;
		int weaponID = equipment[(int)eEquipmentSlot::Melee];

		if (weaponID == -1)
			return false;
	}

	if (auto* characterStateComponent = entity->GetComponent<CharacterStateComponent>())
	{
		if (characterStateComponent->IsAttacking)
			return false;
	}

	return true;
}