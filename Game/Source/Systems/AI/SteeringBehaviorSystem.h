#pragma once
#include "Base/System.h"
	

class SteeringBehaviorSystem : public System
{
public:
	SteeringBehaviorSystem();
	~SteeringBehaviorSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:
	void UpdateWanderBehavior(float aDeltaTime);
	void UpdateFlockBehavior(float aDeltaTime);
	void UpdateSeekBehavior(float aDeltaTime);
	void UpdateFleeBehavior(float aDeltaTime);
};