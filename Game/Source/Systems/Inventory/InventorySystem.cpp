#include "Pch.h"
#include "InventorySystem.h"

InventorySystem::InventorySystem(Hi_Engine::World& world)
	: System{ world, Hi_Engine::eUpdatePhase::Update }
{
}
