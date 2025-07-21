#pragma once
#include <chrono>
#include <iostream>
#include "../IService.h"

namespace Hi_Engine
{
	// TODO; fix this class...

	class TimeService : public IService
	{
	public:
		TimeService();

		// ==================== Core ====================
		void Update();

		// ==================== Queries ====================
		[[nodiscard]] float GetDeltaTime() const;

		[[nodiscard]] float GetAverageFPS() const;

		[[nodiscard]] double GetTotalTime() const;

		[[nodiscard]] double GetFrameTime() const;

	private:
		// ==================== Type Aliases ====================
		using Clock = std::chrono::high_resolution_clock;

		// ==================== Data Members ====================
		std::chrono::time_point<Clock> m_previousTimePoint;
		std::chrono::duration<double> m_deltaTime, m_totalTime;
		
		float m_avgFPS = 0.f;
		int	m_totalFrames = 0;
		float m_elapsedTime = 0.f; // rename TotalTime?!

		float m_averageDeltaTime = 0.f;
		int m_numFrames = 0;
		float m_totalDeltaTime = 0.f;
	};
}