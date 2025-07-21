#pragma once

namespace Hi_Engine
{

	//#if USE_TIMER

#if DEBUG
// #define PROFILE_FUNCTION() ScopedTimer time{__func__}
#define PROFILE_FUNCTION(name) ScopedTimer scopedTimer{name}
#else
#define PROFILE_FUNCTION()
#endif

	class ScopedTimer
	{
		using ClockType = std::chrono::steady_clock;

	public:
		ScopedTimer(const char* funcName)
			: m_funcName{ funcName }, m_start{ ClockType::now() }
		{
		}

		ScopedTimer(const ScopedTimer&) = delete;
		ScopedTimer(ScopedTimer&&) = delete;

		ScopedTimer& operator=(const ScopedTimer) = delete;
		ScopedTimer& operator=(ScopedTimer&&) = delete;

		~ScopedTimer()
		{
			auto stop = ClockType::now();
			auto duration = (stop - m_start);

			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
			std::cout << m_funcName << " ms " << ms << "\n";
		}

	private:
		const char* m_funcName;
		const ClockType::time_point m_start;
	};
}