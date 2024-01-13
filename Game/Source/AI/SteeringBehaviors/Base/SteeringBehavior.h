#pragma once

namespace CU = CommonUtilities;

// Consider making all Behaviors components? C_WanderBehavior, etc... (?)
class SteeringBehavior
{
public:
	~SteeringBehavior() = default;

	virtual void Update(float aDeltaTime) = 0;

	virtual const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& aVelocity) = 0;
	virtual const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity) { return {}; }

	// put funcitons like seek, arrive, etc here?? maybe make namespacfe??
};

