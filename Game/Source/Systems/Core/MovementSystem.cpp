#include "Pch.h"
#include "MovementSystem.h"
#include "Components/GameplayComponents.h"

MovementSystem::MovementSystem(Hi_Engine::World& world)
	: System{ world, Hi_Engine::eUpdatePhase::Update }
{
}

void MovementSystem::Update(float deltaTime)
{
	auto view = m_world.GetComponentView<VelocityComponent, Hi_Engine::TransformComponent>();
}