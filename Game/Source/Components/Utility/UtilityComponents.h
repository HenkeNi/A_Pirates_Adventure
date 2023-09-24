#pragma once
#include "../Base/ComponentBase.h"
#include "Data/Enumerations.h"



 
struct WorldTimeComponent : public ComponentBase
{
	unsigned m_day;

	eTimeOfDay m_timeOfDay;

	float m_currentDayProgress = 0.f;
	float m_dayDuration = 20.f;


	static const int s_dayDurationInRealWorldMinues = 2; // FIX!
	// bool shouldSkipDay?
};





struct TimerComponent : public ComponentBase
{
	float m_elapsed;
	float m_duration;
	bool m_isRunning = false;

	// std::function<void()>	m_callback = nullptr; ?? or observers??
};


struct SpawnComponent : public ComponentBase
{
	std::string m_spawned;
	float		m_interval = 2.f;	// Todo; Give small individual delay..
	float		m_elapsedTime = 0.f;
	int			m_amount = 10;
	int			m_spawnedAmount = 0; // Rename..
};