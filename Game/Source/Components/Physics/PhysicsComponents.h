#pragma once
#include "../Base/ComponentBase.h"
#include "../Data/Enumerations.h"

namespace CU = CommonUtilities;


struct VelocityComponent : public ComponentBase
{
	CU::Vector3<float>	Velocity;
	float				VelocityMax;
	
	CU::Vector3<float>	Acceleration;
	float				Speed;
	// Speed? direction?
};






struct ColliderComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
	CU::Vector3<float>					Offset;
	eCollisionLayer						Layer;
	bool								IsStatic;					// enum for type (trigger, static?
};




// inherit from ColliderComponent?
struct RectangleColliderComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float>	Collider; 
	bool								IsStatic;
	// isTrigger?
};


struct CircleColliderComponent : public ComponentBase
{
};







struct CollisionComponent : public ComponentBase
{

	bool IsTrigger;
};


// staticCollider & DynamicCollider