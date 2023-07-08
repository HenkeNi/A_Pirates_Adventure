#pragma once
#include "Base/System.h"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();

	void Receive(Message& aMsg)			override;
	void LateUpdate(float aDeltaTime)	override;

	// TODO; abstract collision checks into functions that can be called from other systems

private:
	// Check collisions
	// Handle Collision / Resolve Collisions
};

