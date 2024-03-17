#pragma once
#include "../Base/SteeringBehavior.h"
#include <Source/Utility/Math/Vectors/Vector.hpp> // NEEDED`?


namespace CU = CommonUtilities;

//namespace
//{
//	using Vec3 = CommonUtilities::Vector3<float>;
//}

class Entity;

class FlockBehavior : public SteeringBehavior
{
public:
	FlockBehavior();

	void Update(float deltaTime) override;

	const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& velocity) override;
	const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& position, const CU::Vector2<float>& velocity) override;


	// Fix both...
	void SetFlockMembers(const std::vector<Entity*>& entities);
	void SetOwner(Entity* entity);

private:
	CU::Vector2<float> CalculateSeparationForce() const;
	CU::Vector2<float> CalculateCohesionForce() const;
	CU::Vector2<float> CalculateAlignmentForce() const; // Rename ComputeAlignment or CalculateAlignment


	std::vector<Entity*> m_flockMembers;
	Entity*				 m_owner;
	
	float m_minSeparationDistance;

	float m_radius; // Put in Component?
	float m_maxForce;

	float m_maxCohesion;

	// static std::vector<
};

// Register all entities with a SteeringBehavior in a pulling station??