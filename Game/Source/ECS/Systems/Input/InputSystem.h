#pragma once
#include "../Base/System.h"


class InputSystem : public System, public Hi_Engine::EventListener
{
public:
	InputSystem();
	~InputSystem();

	void HandleEvent(Hi_Engine::InputEvent& inputEvent)	override;
	void Update(float DeltaTime)						override;

	void SetSignature() override;
};