#include "Pch.h"
#include "TimeSystem.h"
#include "Components/Utility/UtilityComponents.h"
#include "ECS/ECS.h"


TimeSystem::TimeSystem()
{
}

TimeSystem::~TimeSystem()
{
}

void TimeSystem::Update(float deltaTime) 
{
	assert(m_ecs && "[TimeSystem::Update] - ECS is not initialized!");

	UpdateWorldTime(deltaTime);
	UpdateTimers(deltaTime);
}

void TimeSystem::SetSignature()
{
	m_signatures.insert({ "WorldTime", m_ecs->GetSignature<WorldTimeComponent>() });
	m_signatures.insert({ "Timers", m_ecs->GetSignature<TimerComponent>() });
}

void TimeSystem::UpdateWorldTime(float deltaTime)
{
	for (auto& worldTimeComponent : m_ecs->GetComponents<WorldTimeComponent>())
	{
		AdvanceTime(worldTimeComponent, deltaTime);

		UpdateDayProgress(worldTimeComponent);
		UpdateTimeOfDay(worldTimeComponent);
	}
}

void TimeSystem::UpdateTimers(float deltaTime)
{	
	auto entities = m_ecs->FindEntities(m_signatures["Timers"]);

	for (Entity entity : entities)
	{
		auto* timerComponent = m_ecs->GetComponent<TimerComponent>(entity);

		if (!timerComponent->IsActive)
			continue;

		timerComponent->Elapsed += deltaTime;
		if (timerComponent->Elapsed >= timerComponent->Duration)
		{
			PostMaster::GetInstance().SendMessage({ eMessage::TimerFinished, entity });
			timerComponent->IsActive = false;

			// remove component?
		}
	}
}

void TimeSystem::AdvanceTime(WorldTimeComponent& worldTime, float deltaTime)
{
	float& elapsedTime = worldTime.ElapsedTimeSinceDayStart;
	elapsedTime += deltaTime;

	if (elapsedTime >= worldTime.DayDuration)
	{
		elapsedTime = 0.f;
		++worldTime.Day;
	}
}

void TimeSystem::UpdateDayProgress(WorldTimeComponent& worldTime)
{
	worldTime.CurrentDayProgress = worldTime.ElapsedTimeSinceDayStart / worldTime.DayDuration;
}

void TimeSystem::UpdateTimeOfDay(WorldTimeComponent& worldTime)
{
	eTimeOfDay previousTimeOfDay = worldTime.TimeOfDay;

	auto found = std::find_if(worldTime.TimeOfDayRanges.begin(), worldTime.TimeOfDayRanges.end(),
		[&](const std::pair<eTimeOfDay, Hi_Engine::Range<float>>& dayDuration)
		{
			return worldTime.CurrentDayProgress >= dayDuration.second.Min && worldTime.CurrentDayProgress <= dayDuration.second.Max;
		});


	if (found != worldTime.TimeOfDayRanges.end())
	{
		worldTime.TimeOfDay = found->first;
		if (worldTime.TimeOfDay != previousTimeOfDay)
		{
			PostMaster::GetInstance().SendMessage({ eMessage::TimeOfDayChanged, worldTime.TimeOfDay });
		}
	}
}
