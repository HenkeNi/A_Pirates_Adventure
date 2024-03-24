#pragma once
#include "../Base/Component.h"
#include "Data/Enumerations.h"



 
struct WorldTimeComponent : public Component
{
	unsigned Day;

	eTimeOfDay TimeOfDay;

	float CurrentDayProgress = 0.f;
	float DayDuration = 20.f;


	static const int DayDurationInRealWorldMinues = 2; // FIX!
	// bool shouldSkipDay?
};





struct TimerComponent : public Component
{
	float Elapsed = 0.f;
	double Timestamp = 0.0;
	float Duration = 0.f;
	bool IsActive = true;


	//	float Duration
	// std::function<void()>	m_callback = nullptr; ?? or observers??
};


struct SpawnComponent : public Component
{
	std::string Spawned;
	float		Interval = 2.f;	// Todo; Give small individual delay..
	float		ElapsedTime = 0.f;
	int			Amount = 10;
	int			SpawnedAmount = 0; // Rename..
};