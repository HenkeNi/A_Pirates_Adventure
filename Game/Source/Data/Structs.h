#pragma once
#include "Enumerations.h"

#include <any>

struct eCompMessage
{
	eMessageType	m_type;
	const std::any& m_data;
};

struct CollisionData // Data used for resolving/handling collisions
{
	unsigned		m_damageDealt = 0;
};