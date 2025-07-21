#include "Pch.h"
#include "PlayerControllerSystem.h"

PlayerControllerSystem::PlayerControllerSystem(Hi_Engine::World& world)
	: System{ world, Hi_Engine::eUpdatePhase::PreUpdate }
{
}