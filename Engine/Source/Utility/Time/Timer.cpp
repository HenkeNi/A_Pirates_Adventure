#include "Pch.h"
#include "Timer.h"


namespace Hi_Engine
{
	Timer::Timer()
		: m_previousTimePoint{ std::chrono::high_resolution_clock::now() }, m_deltaTime{ 0 }, m_totalTime{ 0 }
	{
	}

	void Timer::Update()
	{
		auto current = std::chrono::high_resolution_clock::now();
		auto elapsed = current - m_previousTimePoint;

		m_deltaTime = elapsed;
		m_totalTime += elapsed;
		m_previousTimePoint = current;

		if (ContainsTimerRequests())
		{
			CheckTimerRequests();
		}
	}

	float Timer::GetDeltaTime() const
	{
		return m_deltaTime.count();
	}

	double Timer::GetTotalTime() const
	{
		return m_totalTime.count();
	}

	void Timer::NotifyOnTimePassed(TimerRequest aRequest)
	{
		aRequest.m_timeOfRequest = GetTotalTime();
		m_timeRequests.push_back(aRequest);
	}

	bool Timer::ContainsTimerRequests() const
	{
		return !m_timeRequests.empty();
	}

	bool Timer::HasTimeElapsed(double aDuration, double aStartTime) const
	{
		return aStartTime + aDuration >= GetTotalTime();
	}

	void Timer::CheckTimerRequests()
	{
		for (int i = m_timeRequests.size() - 1; i >= 0; --i)
		{
			if (HasTimeElapsed(m_timeRequests[i].m_durationInSecs, m_timeRequests[i].m_timeOfRequest))
			{
				m_timeRequests[i].m_callback();
				m_timeRequests.erase(m_timeRequests.begin() + i);
			}
		}
	}
}