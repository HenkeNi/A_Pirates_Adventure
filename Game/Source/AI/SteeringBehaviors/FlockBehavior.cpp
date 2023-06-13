#include "Pch.h"
#include "FlockBehavior.h"



FlockBehavior::FlockBehavior()
{
}

void FlockBehavior::Update(float aDeltaTime)
{
}

const CU::Vector3<float> FlockBehavior::GetSteeringForce(const CU::Vector3<float>& aVelocity)
{
	return {};
}

const CU::Vector3<float> FlockBehavior::GetSteeringForce(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aVelocity)
{
	return {};
}

CU::Vector3<float> FlockBehavior::GetSeparationForce() const
{
	CU::Vector3<float> separationForce = { 0.f, 0.f, 0.f };


	return {};
}

CU::Vector3<float> FlockBehavior::GetCohesionForce() const
{
	return {};
}

CU::Vector3<float> FlockBehavior::GetAlignmentForce() const
{
	return {};
}