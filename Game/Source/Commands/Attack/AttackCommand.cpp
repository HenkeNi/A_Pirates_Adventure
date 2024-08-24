#include "Pch.h"
#include "AttackCommand.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Components/Core/CoreComponents.h"
#include "ECS.h"


AttackCommand::AttackCommand(ECS& ecs)
	: Command{ ecs }
{
}

void AttackCommand::Execute(Entity entity)
{
	if (!entity)
		return;

	if (auto* characterStateComponent = m_ecs.GetComponent<CharacterStateComponent>(entity))
	{
		characterStateComponent->IsAttacking = true;
	}

	// get equipped weapon instead..
	if (auto* equipmentComponent = m_ecs.GetComponent<EquipmentComponent>(entity))
	{
		int weaponID = equipmentComponent->EquippedItemIDs[(int)eEquipmentSlot::Melee];
		// fetch weapon from entitymanager?!
	}
	
	if (auto* attackComponent = m_ecs.GetComponent<AttackComponent>(entity))
	{
		// attackComponent->IsEnabled = true;
	}

	PostMaster::GetInstance().SendMessage({ eMessage::EntityAttacked, entity }); // only send if no attack animation?
	// send event?
}

// Not called...
bool AttackCommand::CanPerform(Entity entity) const
{
	if (!entity)
		return false;

	if (auto* equipmentComponent = m_ecs.GetComponent<EquipmentComponent>(entity))
	{
		auto equipment = equipmentComponent->EquippedItemIDs;
		int weaponID = equipment[(int)eEquipmentSlot::Melee];

		if (weaponID == -1)
			return false;
	}

	if (auto* characterStateComponent = m_ecs.GetComponent<CharacterStateComponent>(entity))
	{
		if (characterStateComponent->IsAttacking)
			return false;
	}

	return true;
}