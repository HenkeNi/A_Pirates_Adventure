#include "Pch.h"
#include "TimeConditions.h"



ElapsedTimeCondition::ElapsedTimeCondition(float duration)
	: m_start{ 0.f }, m_duration{ duration }
{
}

void ElapsedTimeCondition::Init()
{
	m_start = 0.f; // TODO: fix this with curent time?!  CU:TIMEr get elapsedTime???
}

bool ElapsedTimeCondition::IsSatisfied(float elapsedTime) const
{
	return elapsedTime >= (m_start + m_duration);
}