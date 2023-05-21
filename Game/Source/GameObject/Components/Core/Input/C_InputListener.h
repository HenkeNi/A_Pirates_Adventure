#pragma once
#include "../../Component.h"


class C_InputListener : public Component, public Hi_Engine::EventListener
{
public:
	C_InputListener();

	void	HandleMessage(const CompMessage& aMsg)	override;
	void	HandleEvent(Hi_Engine::KeyEvent& anEvent)   override;


private:
	// store commands?? or keys??
	// function pointer?? or notify components??
};
