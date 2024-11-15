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
	assert(m_ecs && "[TimeSystem - ERROR]: ECS is not initialized!");

	UpdateWorldTime(deltaTime);
	UpdateTimers(deltaTime);
}

void TimeSystem::SetSignature()
{
	m_signatures.insert({ "WorldTime", m_ecs->GetSignature<WorldTimeComponent>() });
	m_signatures.insert({ "Timers", m_ecs->GetSignature<TimerComponent>() });
}

//FVector4 TimeSystem::CalculateDaylightColor(Entity* worldTimeEntity)
//{
//	// put elsewhere????
//	static std::unordered_map<eTimeOfDay, FVector4> daylights;
//	daylights.insert(std::make_pair(eTimeOfDay::Dawn, FVector4{ 0.9804f,	0.7725f,	0.5529f,	1.f }));
//	//daylights.insert(std::make_pair(eTimeOfDay::Day, FVector4{ 0.9569f,	0.8471f,	0.6706f,	1.f }));
//	daylights.insert(std::make_pair(eTimeOfDay::Day, FVector4{ 1.f,	1.f,	1.f,	1.f }));
//	daylights.insert(std::make_pair(eTimeOfDay::Dusk, FVector4{ 0.89f,		0.68f,		0.42f,		1.f }));
//	daylights.insert(std::make_pair(eTimeOfDay::Night, FVector4{ 0.3f,	0.3f,		0.3f,		1.f }));
//
//	if (worldTimeEntity)
//	{
//		if (auto* worldTimeComponent = worldTimeEntity->GetComponent<WorldTimeComponent>())
//		{
//			float progress = worldTimeComponent->CurrentDayProgress;
//			//return Hi_Engine::Lerp(daylights.at(eTimeOfDay::Day), daylights.at(eTimeOfDay::Night), progress);
//			return { 1.f, 1.f, 1.f, 1.f };
//		}
//	}
//
//	return FVector4();
//}

void TimeSystem::UpdateWorldTime(float deltaTime)
{
	auto& worldTimeComponents = m_ecs->GetComponents<WorldTimeComponent>();

	for (auto& worldTimeComponent : worldTimeComponents)
	{
		float& elapsedTime = worldTimeComponent.ElapsedTimeSinceDayStart;

		elapsedTime += deltaTime;
		if (elapsedTime >= worldTimeComponent.DayDuration)
		{
			elapsedTime = 0.f;
			++worldTimeComponent.Day;
		}

		worldTimeComponent.CurrentDayProgress = worldTimeComponent.ElapsedTimeSinceDayStart / worldTimeComponent.DayDuration;

		eTimeOfDay timeOfDay = worldTimeComponent.TimeOfDay;

		auto found = std::find_if(worldTimeComponent.TimeOfDayRanges.begin(), worldTimeComponent.TimeOfDayRanges.end(),
			[&](const std::pair<eTimeOfDay, Hi_Engine::Range<float>>& dayDuration)
			{
				return worldTimeComponent.CurrentDayProgress >= dayDuration.second.Min && worldTimeComponent.CurrentDayProgress <= dayDuration.second.Max;
			});

		if (found != worldTimeComponent.TimeOfDayRanges.end())
		{
			worldTimeComponent.TimeOfDay = found->first;
			if (worldTimeComponent.TimeOfDay != timeOfDay)
			{
				PostMaster::GetInstance().SendMessage({ eMessage::TimeOfDayChanged, worldTimeComponent.TimeOfDay });
			}
		}

		// std::cout << worldTimeComponent->CurrentDayProgress << "\n";
	}
}

//void TimeSystem::SetTimeOfDay(Entity* worldTimeEntity)
//{
//	if (!worldTimeEntity)
//		return;
//
//	auto* worldTimeComponent = worldTimeEntity->GetComponent<WorldTimeComponent>();
//
//	eTimeOfDay timeOfDay = worldTimeComponent->TimeOfDay;
//
//	auto found = std::find_if(worldTimeComponent->TimeOfDayRanges.begin(), worldTimeComponent->TimeOfDayRanges.end(),
//		[&](const std::pair<eTimeOfDay, Hi_Engine::Range<float>>& dayDuration)
//		{
//			return worldTimeComponent->CurrentDayProgress >= dayDuration.second.Min && worldTimeComponent->CurrentDayProgress <= dayDuration.second.Max;
//			//return Hi_Engine::Math::RangeContains(worldTimeComponent->CurrentDayProgress, range);
//		});
//
//	if (found != worldTimeComponent->TimeOfDayRanges.end())
//	{
//		worldTimeComponent->TimeOfDay = found->first;
//		if (worldTimeComponent->TimeOfDay != timeOfDay)
//		{
//			PostMaster::GetInstance().SendMessage({ eMessage::TimeOfDayChanged, worldTimeComponent->TimeOfDay });
//		}
//	}
//}

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
