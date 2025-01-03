#pragma once
#include "Modules/Module.h"
#include "Threading/ThreadPool.h"
#include "Time/Timer.h"

namespace Hi_Engine
{
	class Utility : public Module
	{
	public:
		Utility(ModuleManager& manager);

		bool Init() override;

		inline ThreadPool& GetThreadPool() { return m_threadPool; }
		inline const Timer& GetTimer() const { return m_timer; }
		inline Timer& GetTimer() { return m_timer; }
	private:
		ThreadPool m_threadPool;
		Timer m_timer;
	};
}