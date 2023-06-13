#pragma once
#include "SteeringBehavior.h"


class FlockBehavior : public SteeringBehavior
{
public:
	FlockBehavior();

	void Update(float aDeltaTime) override;

	const CU::Vector3<float> GetSteeringForce(const CU::Vector3<float>& aVelocity) override;
	const CU::Vector3<float> GetSteeringForce(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aVelocity) override;

private:
	CU::Vector3<float> GetSeparationForce() const;
	CU::Vector3<float> GetCohesionForce() const;
	CU::Vector3<float> GetAlignmentForce() const;


	// static std::vector<
};
