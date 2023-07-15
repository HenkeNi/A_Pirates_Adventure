#pragma once
#include "../Base/ComponentBase.h"


struct TimerComponent : public ComponentBase
{
	float m_elapsed;
	float m_duration;
	bool m_isRunning = false;
};