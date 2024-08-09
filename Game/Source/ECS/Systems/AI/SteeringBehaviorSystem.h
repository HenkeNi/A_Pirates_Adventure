#pragma once
#include "../Base/System.h"
	

class SteeringBehaviorSystem : public System
{
public:
	SteeringBehaviorSystem();
	~SteeringBehaviorSystem();

	void Update(float deltaTime)	override;
	void SetSignature() override;

private:
	void UpdateWanderBehavior(float deltaTime);
	void UpdateFlockBehavior(float deltaTime);
	void UpdateSeekBehavior(float deltaTime);
	void UpdateFleeBehavior(float deltaTime);

};