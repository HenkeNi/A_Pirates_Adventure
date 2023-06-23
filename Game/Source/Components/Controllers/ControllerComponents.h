#pragma once
#include "../ComponentBase.h"

// or just ControllerComponent??
struct PlayerControllerComponent : ComponentBase
{
	bool	m_isAttacking;
	float	m_attackPower;
};