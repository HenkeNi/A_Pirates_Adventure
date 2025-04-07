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

	eTimeOfDay TimeOfDay;
	float DayDuration; // = 20.f;
	float ElapsedTimeSinceDayStart; // = 0.f;
	float CurrentDayProgress; // = 0.f;
	unsigned Day; // = 0;
};