#pragma once


struct WorldTimeComponent
{
	enum class eTimeOfDay
	{
		Dawn,
		Day,
		Dusk,
		Night
	};

	float DayDuration = 20.f;
	eTimeOfDay TimeOfDay;
	float ElapsedTimeSinceDayStart = 0.f;
	float CurrentDayProgress = 0.f;
	unsigned Day = 0;
};