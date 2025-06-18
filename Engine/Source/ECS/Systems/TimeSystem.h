#pragma once
#include "System.h"

namespace Hi_Engine
{
	class Timer;

	class TimeSystem : public System
	{
	public:
		TimeSystem(World& world, Timer& timer);

		void Update(float deltaTime) override;
		eUpdatePhase GetUpdatePhase() const override;

	private:	
		Timer& m_timer;
	};
}