#pragma once
#include "Enumerations.h"


 
struct WorldTimeComponent
{	
	std::unordered_map<eTimeOfDay, Hi_Engine::Range<float>> TimeOfDayRanges;
	eTimeOfDay TimeOfDay;
	float DayDuration = 20.f;
	float ElapsedTimeSinceDayStart = 0.f;
	float CurrentDayProgress = 0.f;
	unsigned Day = 0;
};

struct TimerComponent
{
	float Elapsed = 0.f;
	double Timestamp = 0.0;
	float Duration = 0.f;
	bool IsActive = true;


	//	float Duration
	// std::function<void()>	m_callback = nullptr; ?? or observers??
};


struct SpawnComponent
{
	std::string Spawned;
	float		SpawnRadius = 30.f;
	float		Interval = 2.f;	// Todo; Give small individual delay..
	float		ElapsedTime = 0.f;
	int			Amount = 10;
	int			SpawnedAmount = 0; // Rename..
};