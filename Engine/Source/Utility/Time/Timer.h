#pragma once
#include "Data/Structs.h"
#include <chrono>

namespace Hi_Engine
{
	class Timer
	{
	public:
		Timer();

		Timer(const Timer&) = delete;
		Timer& operator=(const Timer&) = delete;

		void		Update();

		float		GetDeltaTime()					const;
		double		GetTotalTime()					const;

		void		NotifyOnTimePassed(TimerRequest aRequest); // Rename; (doesnt notify... isntead does callback...)

	private:
		bool		ContainsTimerRequests()								const; // rename??
		bool		HasTimeElapsed(double aDuration, double aStartTime)	const;
		void		CheckTimerRequests();

		std::chrono::time_point<std::chrono::high_resolution_clock> m_previousTimePoint;
		std::chrono::duration<double>								m_deltaTime, m_totalTime;
		
		std::vector<TimerRequest> m_timeRequests; // Use observer pattern instead?? - need to create an observer class...

		//std::vector<TimeObserver> m_timeObservers;
		//std::unordered_map<TimeObserver*, TimeNotificationRequest> m_observers;
	};
}