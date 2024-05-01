#pragma once

// Consider making all Behaviors components? C_WanderBehavior, etc... (?)
class SteeringBehavior
{
public:
	~SteeringBehavior() = default;

	virtual void Update(float deltaTime) = 0;

	virtual const FVector2 GetSteeringForce(const FVector2& velocity) = 0;
	virtual const FVector2 GetSteeringForce(const FVector2& position, const FVector2& velocity) { return {}; }

	// put funcitons like seek, arrive, etc here?? maybe make namespacfe??
};

