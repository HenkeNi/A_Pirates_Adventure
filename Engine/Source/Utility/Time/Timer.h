#pragma once
#include "../Data/Structs.h"
#include <chrono>

namespace Hi_Engine
{
	// make static?
	class Timer	
	{
	public:
		Timer();

		Timer(const Timer&) = delete;
		Timer& operator=(const Timer&) = delete;

		void		Update();

		float		GetDeltaTime()					const;
		float		GetAverageDeltaTime()			const;	// NEEDED??
		float		GetAverageFPS()					const;
		double		GetTotalTime()					const;

		void		NotifyOnTimePassed(TimerRequest aRequest); // Rename; (doesnt notify... isntead does callback...)

	private:
		bool		ContainsTimerRequests()								const; // rename??
		bool		HasTimeElapsed(double aDuration, double aStartTime)	const;
		void		CheckTimerRequests();

		std::chrono::time_point<std::chrono::high_resolution_clock> m_previousTimePoint;
		std::chrono::duration<double>								m_deltaTime, m_totalTime;
		
		// DONT??
		std::vector<TimerRequest> m_timeRequests; // Use observer pattern instead?? - need to create an observer class...

		float	m_averageFPS = 0.f;
		int		m_totalFrames = 0;
		float	m_elapsedTime = 0.f; // rename TotalTime?!

		float	m_averageDeltaTime = 0.f;
		int m_numFrames = 0;
		float m_totalDeltaTime = 0.f;
		//std::vector<TimeObserver> m_timeObservers;
		//std::unordered_map<TimeObserver*, TimeNotificationRequest> m_observers;
	};
}