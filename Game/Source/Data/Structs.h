#pragma once
#include "Enumerations.h"

#include <any>


struct CompMessage
{
	eComponentMessage	m_messageType;
	const std::any&		m_data;
};

struct CollisionData // Data used for resolving/handling collisions
{
	unsigned m_damageDealt = 0;
};

struct Timer
{
	float m_elapsed;
	float m_duration;
};