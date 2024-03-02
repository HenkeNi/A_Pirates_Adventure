#include "Pch.h"
#include "AttackCommand.h"
#include "Entities/Entity.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Components/Core/CoreComponents.h"


AttackCommand::AttackCommand()
{
}

void AttackCommand::Execute(Entity* anEntity)
{
	if (!anEntity)
		return;

	if (auto* characterStateComponent = anEntity->GetComponent<CharacterStateComponent>())
	{
		characterStateComponent->IsAttacking = true;
	}

	//// get equipped weapon instead..
	//if (auto* equipmentComponent = anEntity->GetComponent<EquipmentComponent>())
	//{
	//	int weaponID = equipmentComponent->EquippedItemIDs[(int)eEquipmentSlot::Melee];
	//	// fetch weapon from entitymanager?!
	//}
	//
	//if (auto* attackComponent = anEntity->GetComponent<AttackComponent>())
	//{
	//	attackComponent->IsEnabled = true;
	//}

	// send event?
}

// Not called...
bool AttackCommand::CanPerform(Entity* anEntity) const
{
	if (!anEntity)
		return false;

	if (auto* equipmentComponent = anEntity->GetComponent<EquipmentComponent>())
	{
		auto equipment = equipmentComponent->EquippedItemIDs;
		int weaponID = equipment[(int)eEquipmentSlot::Melee];

		if (weaponID == -1)
			return false;
	}

	if (auto* characterStateComponent = anEntity->GetComponent<CharacterStateComponent>())
	{
		if (characterStateComponent->IsAttacking)
			return false;
	}

	return true;
}