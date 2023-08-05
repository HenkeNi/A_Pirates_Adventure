#pragma once
#include "../Base/ComponentBase.h"

namespace CU = CommonUtilities;


struct VelocityComponent : public ComponentBase
{
	CU::Vector3<float>	m_velocity;
	float				m_velocityMax;
	
	CU::Vector3<float>	m_acceleration;
	float				m_speed;
	// Speed? direction?
};


// Use to determine if colliding
struct RectangleColliderComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float>	m_collider; 
	bool								m_isStatic;
	// isStaic?
};


struct CircleColliderComponent : public ComponentBase
{
};



