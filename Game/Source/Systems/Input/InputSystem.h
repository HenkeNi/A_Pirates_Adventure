#pragma once
#include "Base/System.h"


class InputSystem : public System, public Hi_Engine::EventListener
{
public:
	InputSystem();
	~InputSystem();

	void HandleEvent(Hi_Engine::InputEvent& anEvent)	override;
	void Receive(Message& aMsg)							override;
	void Update(float aDeltaTime)						override;

private:
};

