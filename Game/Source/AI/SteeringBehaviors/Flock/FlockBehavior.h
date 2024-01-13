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

	void Update(float aDeltaTime) override;

	const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& aVelocity) override;
	const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity) override;


	// Fix both...
	void SetFlockMembers(const std::vector<Entity*>& someEntities);
	void SetOwner(Entity* anEntity);

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