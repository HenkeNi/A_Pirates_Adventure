#include "Pch.h"
#include "TimeSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Utility/UtilityComponents.h"


TimeSystem::TimeSystem()
{
	//PostMaster::GetInstance().Subscribe(eMessage::Entit, this);
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


float TimeSystem::GetAverageDeltaTime(float deltaTime) const
{
	static float averageDeltaTime = 0.f;
	static float totalTime = 0.f;
	static int numFrames = 0;

	++numFrames;
	if ((totalTime += deltaTime) > 10.f) // FIX magic number (number of frames to average)
	{
		averageDeltaTime = totalTime / numFrames;
		totalTime = 0.f;
		numFrames = 0;
	}

	return averageDeltaTime;
}

void TimeSystem::UpdateWorldTime(float deltaTime)
{
	auto* entity = m_entityManager->FindFirst<WorldTimeComponent>();

	if (!entity)
		return;

	float scaledDeltaTime = deltaTime * GetAverageDeltaTime(deltaTime);

	//const float timeScaleFactory = WorldTimeComponent::s_dayDurationInRealWorldMinues * fps / averageDeltaTime;

	auto worldTimeComponent = entity->GetComponent<WorldTimeComponent>();

	float& progress = worldTimeComponent->CurrentDayProgress;


	//if ((progress += aDeltaTime) >= worldTimeComponent->m_dayDuration)
	if ((progress += scaledDeltaTime) >= worldTimeComponent->DayDuration)
	{
		progress = 0.f;
		worldTimeComponent->Day += 1; // Notify on day changed

		std::cout << "New dayy!";
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
