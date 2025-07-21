#include "Pch.h"
#include "WorldTimeSystem.h"
#include "Components/GameplayComponents.h"

WorldTimeSystem::WorldTimeSystem(Hi_Engine::World& world)
	: System{ world, Hi_Engine::eUpdatePhase::Update }
{
	PostMaster::GetInstance().Subscribe(eMessage::GameStarted, this);
}

WorldTimeSystem::~WorldTimeSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::GameStarted, this);
}

void WorldTimeSystem::Receive(Message& message)
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

void WorldTimeSystem::OnCreated()
{
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
