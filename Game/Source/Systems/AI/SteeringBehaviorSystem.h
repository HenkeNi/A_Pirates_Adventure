#pragma once
#include "Base/System.h"
	

class SteeringBehaviorSystem : public System
{
	SteeringBehaviorSystem();
	~SteeringBehaviorSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

};