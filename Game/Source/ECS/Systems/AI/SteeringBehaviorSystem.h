#pragma once
#include "../Base/System.h"
	

class SteeringBehaviorSystem : public System
{
public:
	SteeringBehaviorSystem();
	~SteeringBehaviorSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

private:
	void UpdateWanderBehavior(float deltaTime);
	void UpdateFlockBehavior(float deltaTime);
	void UpdateSeekBehavior(float deltaTime);
	void UpdateFleeBehavior(float deltaTime);

};