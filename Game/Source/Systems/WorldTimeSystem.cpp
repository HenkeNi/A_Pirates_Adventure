#include "Pch.h"
#include "WorldTimeSystem.h"
#include "Components/GameplayComponents.h"

WorldTimeSystem::WorldTimeSystem(Hi_Engine::ECSCoordinator& ecs)
	: System{ ecs }
{
}

void WorldTimeSystem::Update(float deltaTime)
{
	for (auto& worldTimeComponent : m_ecs.GetComponents<WorldTimeComponent>())
	{
		AdvanceTime(worldTimeComponent, deltaTime);

		UpdateDayProgress(worldTimeComponent);
		UpdateTimeOfDay(worldTimeComponent);
	}
}

Hi_Engine::eUpdatePhase WorldTimeSystem::GetUpdatePhase() const
{
	return Hi_Engine::eUpdatePhase::Update;
}

void WorldTimeSystem::AdvanceTime(WorldTimeComponent& component, float deltaTime)
{
}

void WorldTimeSystem::UpdateDayProgress(WorldTimeComponent& component)
{
}

void WorldTimeSystem::UpdateTimeOfDay(WorldTimeComponent& component)
{
}
