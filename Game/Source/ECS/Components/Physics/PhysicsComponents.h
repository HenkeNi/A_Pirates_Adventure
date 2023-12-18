#pragma once
#include "../Base/Component.h"
#include "../DataTypes/Enumerations.h"

namespace CU = CommonUtilities;


struct VelocityComponent : public Component
{
	CU::Vector3<float>	Velocity;
	float				VelocityMax;
	
	CU::Vector3<float>	Acceleration;
	float				Speed;
	// Speed? direction?


};






struct ColliderComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
	CU::Vector3<float>					Offset;
	eCollisionLayer						Layer;
	bool								IsStatic;					// enum for type (trigger, static?
};




// inherit from ColliderComponent?
struct RectangleColliderComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider; 
	bool								IsStatic;
	// isTrigger?
};


struct CircleColliderComponent : public Component
{
};







struct CollisionComponent : public Component
{

	bool IsTrigger;
};


// staticCollider & DynamicCollider