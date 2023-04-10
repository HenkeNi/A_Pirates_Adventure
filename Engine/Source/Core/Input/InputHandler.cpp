#include "Pch.h"
#include "InputHandler.h"
#include "Messaging/Dispatcher/Dispatcher.h"
#include "Messaging/Events/SystemEvents/SystemEvents.h"


namespace Hi_Engine
{
	InputHandler::InputHandler()
	{
	}

	InputHandler::~InputHandler()
	{
	}

	void InputHandler::Init()
	{

	}

	void InputHandler::ProcessInput()
	{
		Dispatcher::GetInstance().AddEvent<MouseEvent>();
		Dispatcher::GetInstance().AddEvent<WindowEvent>();
		Dispatcher::GetInstance().AddEvent<KeyEvent>();
	}

	void InputHandler::MapCommand(eInputType aType, Command* aCommand)
	{
		//m_inputCommands.insert_or_assign(aType, aCommand);
	}

	void InputHandler::KeyCallback(GLFWwindow* aWindow, int aKey, int aScanCode, int anAction, int someMods)
	{
		// replace key with an int?? (m_commands[GLFW_Key_W] = ....???

		switch (aKey)
		{
		case GLFW_KEY_W:
				break;
		case GLFW_KEY_A:
				break;
		case GLFW_KEY_S:
				break;
		case GLFW_KEY_D:
			//m_inputCommands[eInputType::Key_ArrowRight] = GetKeyState(anAction);
				break;
		}
	}

	eInputState	InputHandler::GetKeyState(int aKey)
	{
		return eInputState::None;
	}
}