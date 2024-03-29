#pragma once

// Consider making all Behaviors components? C_WanderBehavior, etc... (?)
class SteeringBehavior
{
public:
	~SteeringBehavior() = default;

	virtual void Update(float deltaTime) = 0;

	virtual const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& velocity) = 0;
	virtual const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& position, const CU::Vector2<float>& velocity) { return {}; }

	// put funcitons like seek, arrive, etc here?? maybe make namespacfe??
};

