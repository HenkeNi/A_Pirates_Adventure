#pragma once
#include "../Component.h"


class C_PlayerController : public Component
{
public:
	C_PlayerController(GameObject* anOwner = nullptr);

	void HandleMessage(CompMessage aMessage)	override;
	void Update(float aDeltaTime)				override;
};

