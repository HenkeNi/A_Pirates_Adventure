#pragma once
#include "../Component.h"

class C_PlayerController : public Component
{
public:
	C_PlayerController(GameObject* anOwner);

	void HandleMessage(eMessageType aType, const std::any& someData)	override;
	void Update(float aDeltaTime)										override;
};
