#pragma once
#include "../ComponentBase.h"

namespace CU = CommonUtilities;

// Rename MotionComponent?
struct VelocityComponent : public ComponentBase
{
	CU::Vector3<float> m_velocity;
	CU::Vector3<float> m_acceleration;
};

