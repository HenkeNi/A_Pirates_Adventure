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

		
		
		
		// Calculate average Delta time
		m_totalDeltaTime += GetDeltaTime();
		++m_numFrames;

		if (m_numFrames >= 20) // Larger tha number of frames to average
		{
			m_averageDeltaTime = m_totalDeltaTime / m_numFrames;
			m_totalDeltaTime = 0.f;
			m_numFrames = 0;
		}
		


		// Calculate average fps
		++m_totalFrames;
		if ((m_elapsedTime += GetDeltaTime()) >= 1.f)
		{
			m_averageFPS = m_totalFrames / m_elapsedTime;
			m_totalFrames = 0;
			m_elapsedTime = 0.f;
		}


		if (ContainsTimerRequests())
		{
			CheckTimerRequests();
		}
	}

	float Timer::GetDeltaTime() const
	{
		return m_deltaTime.count();
	}

	float Timer::GetAverageFPS() const
	{
		return m_averageFPS;
	}

	double Timer::GetTotalTime() const
	{
		return m_totalTime.count();
	}

	void Timer::NotifyOnTimePassed(TimerRequest request)
	{
		request.TimeOfRequest = GetTotalTime();
		m_timeRequests.push_back(request);
	}

	bool Timer::ContainsTimerRequests() const
	{
		return !m_timeRequests.empty();
	}

	bool Timer::HasTimeElapsed(double duration, double startTime) const
	{
		return startTime + duration >= GetTotalTime();
	}

	void Timer::CheckTimerRequests()
	{
		// TODO: fix..
		/*for (std::size_t i = m_timeRequests.size() - 1; i >= 0; --i)
		{
			if (HasTimeElapsed(m_timeRequests[i].DurationInSecs, m_timeRequests[i].TimeOfRequest))
			{
				m_timeRequests[i].Callback();
				m_timeRequests.erase(m_timeRequests.begin() + i);
			}
		}*/
	}
}