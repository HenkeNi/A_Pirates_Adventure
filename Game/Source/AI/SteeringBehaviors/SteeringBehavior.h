#pragma once


// Consider making all Behaviors components? C_WanderBehavior, etc... (?)
class SteeringBehavior
{
public:
	~SteeringBehavior() = default;

	virtual void Update(float aDeltaTime) = 0;

	virtual const CU::Vector3<float> GetSteeringForce(const CU::Vector3<float>& aVelocity) = 0;
	virtual const CU::Vector3<float> GetSteeringForce(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aVelocity) { return {}; }

	// put funcitons like seek, arrive, etc here?? maybe make namespacfe??
};

