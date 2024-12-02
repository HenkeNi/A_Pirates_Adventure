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
	double Timestamp = 0.0;
	float Elapsed = 0.f;
	float Duration = 0.f;
	bool IsActive = true;

	// Add callback? std::function<void()>
};



//struct EditorComponent
//{
//
//};