#include "Pch.h"
#include "CombatSystem.h"

CombatSystem::CombatSystem(Hi_Engine::World& world)
	: System{ world,  Hi_Engine::eUpdatePhase::Update }
{
}
