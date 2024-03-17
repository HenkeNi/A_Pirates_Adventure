#pragma once
#include "../Base/System.h"


class InputSystem : public System, public Hi_Engine::EventListener
{
public:
	InputSystem();
	~InputSystem();

	void HandleEvent(Hi_Engine::InputEvent& inputEvent)	override;
	void Receive(Message& message)						override;
	void Update(float DeltaTime)						override;
};