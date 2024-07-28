#pragma once
#include "../Base/SteeringBehavior.h"

class FlockBehavior : public SteeringBehavior
{
public:
	FlockBehavior();

	void Update(float deltaTime) override;

	const FVector2 GetSteeringForce(const FVector2& velocity) override;
	const FVector2 GetSteeringForce(const FVector2& position, const FVector2& velocity) override;


	// Fix both...
	//void SetFlockMembers(const std::vector<Entity>& entities);
	//void SetOwner(Entity entity);

private:
	FVector2 CalculateSeparationForce() const;
	FVector2 CalculateCohesionForce() const;
	FVector2 CalculateAlignmentForce() const; // Rename ComputeAlignment or CalculateAlignment


	//std::vector<Entity> m_flockMembers;
	//Entity				 m_owner;
	
	float m_minSeparationDistance;

	float m_radius; // Put in Component?
	float m_maxForce;

	float m_maxCohesion;

	// static std::vector<
};

// Register all entities with a SteeringBehavior in a pulling station??