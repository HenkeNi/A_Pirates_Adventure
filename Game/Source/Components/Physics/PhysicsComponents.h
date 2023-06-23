#pragma once
#include "../ComponentBase.h"

namespace CU = CommonUtilities;

// Rename MotionComponent? or MovementComponent?
struct VelocityComponent : public ComponentBase
{
	CU::Vector3<float>	m_velocity;
	float				m_velocityMax;
	
	CU::Vector3<float>	m_acceleration;
	float				m_speed;
	// Speed? direction?
};

