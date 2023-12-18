#include "Pch.h"
#include "TimeSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Utility/UtilityComponents.h"


TimeSystem::TimeSystem()
{
}

TimeSystem::~TimeSystem()
{
}

void TimeSystem::Receive(Message& aMsg)	
{

}

void TimeSystem::Update(float aDeltaTime) 
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<WorldTimeComponent>();

	float scaledDeltaTime = aDeltaTime * GetAverageDeltaTime(aDeltaTime);

	//const float timeScaleFactory = WorldTimeComponent::s_dayDurationInRealWorldMinues * fps / averageDeltaTime;

	for (auto* entity : entities)
	{
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
}


float TimeSystem::GetAverageDeltaTime(float aDeltaTime) const
{
	static float averageDeltaTime = 0.f;
	static float totalTime = 0.f;
	static int numFrames = 0;

	++numFrames;
	if ((totalTime += aDeltaTime) > 10.f) // FIX magic number (number of frames to average)
	{
		averageDeltaTime = totalTime / numFrames;
		totalTime = 0.f;
		numFrames = 0;
	}

	return averageDeltaTime;
}