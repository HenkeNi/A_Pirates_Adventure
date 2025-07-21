#include "Pch.h"
#include "EquipmentSystem.h"

EquipmentSystem::EquipmentSystem(Hi_Engine::World& world)
	: System{ world, Hi_Engine::eUpdatePhase::Update }
{
}
