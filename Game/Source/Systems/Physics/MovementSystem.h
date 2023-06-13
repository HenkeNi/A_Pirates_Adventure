#pragma once
#include "Base/System.h"


class MovementSystem : public System
{
public:
	MovementSystem();
	~MovementSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;


	// All components that have transform and velocity...

private:
};

