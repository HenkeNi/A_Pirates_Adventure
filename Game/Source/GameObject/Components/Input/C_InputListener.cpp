#include "Pch.h"
#include "C_InputListener.h"


void C_InputListener::HandleMessage(const CompMessage& aMsg)
{
}

void C_InputListener::HandleEvent(Hi_Engine::KeyEvent& anEvent)
{
	if (anEvent.GetKeyCode() == 1)
	{
		static int i = 10;
		i += 10;
	}
}
