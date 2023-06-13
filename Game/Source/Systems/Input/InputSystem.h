#pragma once
#include "Base/System.h"


class InputSystem : public System
{
public:
	InputSystem();
	~InputSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:
};

