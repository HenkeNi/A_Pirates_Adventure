#include "Pch.h"
#include "TimeService.h"


namespace Hi_Engine
{
	TimeService::TimeService()
		: m_previousTimePoint{ std::chrono::high_resolution_clock::now() }, m_deltaTime{ 0 }, m_totalTime{ 0 }
	{
	}

	void TimeService::Update()
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
			m_avgFPS = m_totalFrames / m_elapsedTime;
			m_totalFrames = 0;
			m_elapsedTime = 0.f;
		}


		/*if (ContainsTimerRequests())
		{
			CheckTimerRequests();
		}*/
	}

	float TimeService::GetDeltaTime() const
	{
		return m_deltaTime.count();
	}

	float TimeService::GetAverageFPS() const
	{
		return m_avgFPS;
	}

	double TimeService::GetTotalTime() const
	{
		return m_totalTime.count();
	}

	double TimeService::GetFrameTime() const
	{
		return 0.0;
	}
}