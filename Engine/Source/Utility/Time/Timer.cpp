#include "Pch.h"
#include "Timer.h"


namespace CommonUtilities
{
	Timer::Timer()
		: myPreviousTimePoint{ std::chrono::high_resolution_clock::now() }, myDeltaTime{ 0 }, myTotalTime{ 0 }
	{
	}

	void Timer::Update()
	{
		auto current = std::chrono::high_resolution_clock::now();
		auto elapsed = current - myPreviousTimePoint;

		myDeltaTime = elapsed;
		myTotalTime += elapsed;
		myPreviousTimePoint = current;
	}

	float Timer::GetDeltaTime() const
	{
		return myDeltaTime.count();
	}

	double Timer::GetTotalTime() const
	{
		return myTotalTime.count();
	}
}