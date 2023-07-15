#pragma once
#include "../Base/ComponentBase.h"

// or just ControllerComponent??
struct PlayerControllerComponent : ComponentBase
{
	bool	m_isAttacking;
	float	m_attackPower;
};



struct EnemyControllerComponent : ComponentBase
{
	// AI => Behavior tree..
};


// Animal Controller?	(steering behavuir?)