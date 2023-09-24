#pragma once
#include "../Base/ComponentBase.h"
#include "../Data/Enumerations.h"

namespace CU = CommonUtilities;


struct VelocityComponent : public ComponentBase
{
	CU::Vector3<float>	m_velocity;
	float				m_velocityMax;
	
	CU::Vector3<float>	m_acceleration;
	float				m_speed;
	// Speed? direction?
};






struct ColliderComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float>	m_collider;
	CU::Vector3<float>					m_offset;
	eCollisionLayer						m_layer;
	bool								m_isStatic;					// enum for type (trigger, static?
};




// inherit from ColliderComponent?
struct RectangleColliderComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float>	m_collider; 
	bool								m_isStatic;
	// isTrigger?
};


struct CircleColliderComponent : public ComponentBase
{
};







struct CollisionComponent : public ComponentBase
{

	bool m_isTrigger;
};


// staticCollider & DynamicCollider