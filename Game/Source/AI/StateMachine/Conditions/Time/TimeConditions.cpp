#include "Pch.h"
#include "TimeConditions.h"



ElapsedTimeCondition::ElapsedTimeCondition(float duration)
	:  m_duration{ duration }, m_timestamp{ 0.0 }
{
}

void ElapsedTimeCondition::Init()
{
	// m_start = 0.f; // TODO: fix this with curent time?!  CU:TIMEr get elapsedTime???
}

bool ElapsedTimeCondition::IsSatisfied(Entity* entity) const
{
	double currentTime = Hi_Engine::Engine::GetTimer().GetTotalTime();

	return currentTime > m_timestamp + m_duration;

	// return elapsedTime >= (m_start + m_duration);
}

void ElapsedTimeCondition::Reset()
{
	m_timestamp = Hi_Engine::Engine::GetTimer().GetTotalTime();
}