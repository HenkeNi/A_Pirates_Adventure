#pragma once
#include "../ComponentBase.h"
#include "../Data/Structs.h"


struct TimerComponent : public ComponentBase
{
	Timer m_timer;
	bool m_isRunning = false;
};