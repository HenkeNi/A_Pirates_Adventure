#pragma once
#include "../Component.h"

class C_EnemyController : public Component
{
public:
	C_EnemyController(GameObject* anOwner);

	void						HandleMessage(eCompMessage aMessage)	override;
	void						Update(float aDeltaTime)				override;
};

