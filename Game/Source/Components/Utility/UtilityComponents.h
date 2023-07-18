#pragma once
#include "../Base/ComponentBase.h"


struct TimerComponent : public ComponentBase
{
	float m_elapsed;
	float m_duration;
	bool m_isRunning = false;
};


struct SpawnComponent : public ComponentBase
{
	std::string m_spawned;
	float		m_interval = 2.f;	// Todo; Give small individual delay..
	float		m_elapsedTime = 0.f;
	int			m_amount = 10;
	int			m_spawnedAmount = 0; // Rename..
};