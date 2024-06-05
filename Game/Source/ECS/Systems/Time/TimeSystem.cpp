#include "Pch.h"
#include "TimeSystem.h"
#include "Entities/EntityManager.h"
#include "Entities/Entity.h"
#include "Components/Utility/UtilityComponents.h"

TimeSystem::TimeSystem()
{
}

TimeSystem::~TimeSystem()
{
	//PostMaster::GetInstance().Unsubscribe(eMessage::EntityCreated, this);
}

void TimeSystem::Receive(Message& message)	
{
	/*auto* entity = std::any_cast<Entity*>(message.GetData());

	if (!entity->HasComponent<TimerComponent>())
		return;

	auto* timer = m_entityManager->Find(entity->GetID());

	auto* timerComponent = timer->GetComponent<TimerComponent>();

	timerComponent->IsActive = true;
	timerComponent->Timestamp = Hi_Engine::Engine::GetTimer().GetTotalTime();*/
}

void TimeSystem::Update(float deltaTime) 
{
	if (!m_entityManager)
		return;

	UpdateWorldTime(deltaTime);
	UpdateTimers(deltaTime);
}

//float TimeSystem::CalculateDayProgression(Entity* entity)
//{
//	if (entity)
//	{
//		if (auto* worldTimeComponent = entity->GetComponent<WorldTimeComponent>())
//		{
//			float progression = worldTimeComponent->TimeSinceDayStart / worldTimeComponent->DayDuration;
//			return progression;
//		}
//	}
//	return 0.f;
//}

FVector4 TimeSystem::CalculateDaylightColor(Entity* worldTimeEntity)
{
	// put elsewhere????
	static std::unordered_map<eTimeOfDay, FVector4> daylights;
	daylights.insert(std::make_pair(eTimeOfDay::Dawn, FVector4{ 0.9804f,	0.7725f,	0.5529f,	1.f }));
	//daylights.insert(std::make_pair(eTimeOfDay::Day, FVector4{ 0.9569f,	0.8471f,	0.6706f,	1.f }));
	daylights.insert(std::make_pair(eTimeOfDay::Day, FVector4{ 1.f,	1.f,	1.f,	1.f }));
	daylights.insert(std::make_pair(eTimeOfDay::Dusk, FVector4{ 0.89f,		0.68f,		0.42f,		1.f }));
	daylights.insert(std::make_pair(eTimeOfDay::Night, FVector4{ 0.3f,	0.3f,		0.3f,		1.f }));

	if (worldTimeEntity)
	{
		if (auto* worldTimeComponent = worldTimeEntity->GetComponent<WorldTimeComponent>())
		{
			float progress = worldTimeComponent->CurrentDayProgress;
			//return Hi_Engine::Lerp(daylights.at(eTimeOfDay::Day), daylights.at(eTimeOfDay::Night), progress);
			return { 1.f, 1.f, 1.f, 1.f };
		}
	}

	return FVector4();
}



//float TimeSystem::GetAverageDeltaTime(float deltaTime) const
//{
//	static float averageDeltaTime = 0.f;
//	static float totalTime = 0.f;
//	static int numFrames = 0;
//
//	++numFrames;
//	if ((totalTime += deltaTime) > 10.f) // FIX magic number (number of frames to average)
//	{
//		averageDeltaTime = totalTime / numFrames;
//		totalTime = 0.f;
//		numFrames = 0;
//	}
//
//	return averageDeltaTime;
//}

void TimeSystem::UpdateWorldTime(float deltaTime)
{
	auto* entity = m_entityManager->FindFirst<WorldTimeComponent>();

	if (!entity)
		return;

	auto* worldTimeComponent = entity->GetComponent<WorldTimeComponent>();

	worldTimeComponent->TimeSinceDayStart += deltaTime;
	if (worldTimeComponent->TimeSinceDayStart >= worldTimeComponent->DayDuration)
	{
		worldTimeComponent->TimeSinceDayStart = 0.f;
		++worldTimeComponent->Day;
	}

	worldTimeComponent->CurrentDayProgress = worldTimeComponent->TimeSinceDayStart / worldTimeComponent->DayDuration;
	//std::cout << "Day Progression: " << worldTimeComponent->CurrentDayProgress << "\n";

	SetTimeOfDay(entity);
}

void TimeSystem::SetTimeOfDay(Entity* worldTimeEntity)
{
	if (!worldTimeEntity)
		return;

	auto* worldTimeComponent = worldTimeEntity->GetComponent<WorldTimeComponent>();

	eTimeOfDay timeOfDay = worldTimeComponent->TimeOfDay;

	auto found = std::find_if(worldTimeComponent->TimeOfDayDurations.begin(), worldTimeComponent->TimeOfDayDurations.end(),
		[&](const std::pair<eTimeOfDay, Hi_Engine::Range<float>>& dayDuration)
		{
			const Hi_Engine::Range<float>& range = dayDuration.second;
			return worldTimeComponent->CurrentDayProgress >=  range.Min && worldTimeComponent->CurrentDayProgress <= range.Max;
			//return Hi_Engine::Math::RangeContains(worldTimeComponent->CurrentDayProgress, range);
		});

	if (found != worldTimeComponent->TimeOfDayDurations.end())
	{
		worldTimeComponent->TimeOfDay = found->first;
		if (worldTimeComponent->TimeOfDay != timeOfDay)
		{
			PostMaster::GetInstance().SendMessage({ eMessage::TimeOfDayChanged, worldTimeComponent->TimeOfDay });
		}
	}
}



void TimeSystem::UpdateTimers(float deltaTime)
{
	auto entities = m_entityManager->FindAll<TimerComponent>();
	
	for (auto& entity : entities)
	{
		auto* timerComponent = entity->GetComponent<TimerComponent>();

		if (!timerComponent->IsActive)
			continue;

		timerComponent->Elapsed += deltaTime;
		if (timerComponent->Elapsed >= timerComponent->Duration)
		{
			PostMaster::GetInstance().SendMessage({ eMessage::TimerFinished, entity });
			timerComponent->IsActive = false;

		}


		////double totalTime = Hi_Engine::Engine::GetTimer().GetTotalTime();

		//// Make static function in TimeSystem???
		//if (timerComponent->Timestamp + timerComponent->Duration > totalTime)
		//{
		//	PostMaster::GetInstance().SendMessage({ eMessage::TimerFinished, entity });
		//	timerComponent->IsActive = false;
		//}
	}
}
