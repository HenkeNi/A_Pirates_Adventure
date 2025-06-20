#include "Pch.h"
#include "WorldTimeSystem.h"
#include "Components/GameplayComponents.h"

WorldTimeSystem::WorldTimeSystem(Hi_Engine::World& world)
	: System{ world }
{
}

void WorldTimeSystem::Update(float deltaTime)
{
	auto view = m_world.GetComponentView<WorldTimeComponent>();

	view.ForEach([=](WorldTimeComponent& component)
		{
			AdvanceTime(component, deltaTime);

			UpdateDayProgress(component);
			UpdateTimeOfDay(component);
		});

	//for (auto& worldTimeComponent : m_ecs.GetComponents<WorldTimeComponent>())
	//{
	//	AdvanceTime(worldTimeComponent, deltaTime);

	//	UpdateDayProgress(worldTimeComponent);
	//	UpdateTimeOfDay(worldTimeComponent);
	//}
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
