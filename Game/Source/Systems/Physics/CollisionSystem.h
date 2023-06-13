#pragma once
#include "Base/System.h"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();

	void Receive(Message& aMsg)			override;
	void LateUpdate(float aDeltaTime)	override;

	

private:
	// Check collisions
	// Handle Collision / Resolve Collisions
};

