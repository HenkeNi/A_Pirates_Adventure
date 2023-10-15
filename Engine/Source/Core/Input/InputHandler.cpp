#include "Pch.h"
#include "InputHandler.h"
#include "Messaging/Dispatcher/Dispatcher.h"
#include "Messaging/Events/SystemEvents/SystemEvents.h"


// #include "Base/Command/Command.h"

namespace Hi_Engine
{
	std::unordered_map<eInputType, eInputState>		InputHandler::s_inputStates;
	glm::vec2										InputHandler::s_mousePosition;
	std::unordered_map<eInputType, Command*>		InputHandler::s_mappedCommands;

	InputHandler::InputHandler()
	{
	}

	InputHandler::~InputHandler()
	{
		for (auto& Command : s_mappedCommands)
		{
			delete Command.second;
		}
	}

	void InputHandler::Init(GLFWwindow* aWindow)
	{
		glfwSetKeyCallback(aWindow, InputHandler::KeyCallback); // Do in InputHandler instead??
		glfwSetCursorPosCallback(aWindow, InputHandler::CursorCallback);
		glfwSetMouseButtonCallback(aWindow, InputHandler::MouseButtonCallback);
	}

	void InputHandler::ProcessInput()
	{
		// TODO: save previous frame's key status?!

		for (const auto& inputState : s_inputStates)
		{
			if (IsCommandMapped(inputState.first) && inputState.second == eInputState::Press)
			{
				// s_mappedCommands[inputState.first]->Execute();
			}
			// for each key... 
				// also send the key's previous frames state...
			Dispatcher::GetInstance().AddEvent<KeyEvent>(inputState.second, (int)inputState.first);
		}

	}

	void InputHandler::ClearCommands()
	{}

	void InputHandler::KeyCallback(GLFWwindow* aWindow, int aKey, int aScanCode, int anAction, int someMods)
	{
		// Maybe; replace key with an int?? (m_commands[GLFW_Key_W] = ....???

		switch (aKey)
		{
		case GLFW_KEY_W:
			s_inputStates[eInputType::Key_W] = GetKeyState(anAction);
			break;
		case GLFW_KEY_A:
			s_inputStates[eInputType::Key_A] = GetKeyState(anAction);	
			break;
		case GLFW_KEY_S:
			s_inputStates[eInputType::Key_S] = GetKeyState(anAction);	
			break;
		case GLFW_KEY_D:
			s_inputStates[eInputType::Key_D] = GetKeyState(anAction);	
			break;
		case GLFW_KEY_SPACE:
			s_inputStates[eInputType::Key_Space] = GetKeyState(anAction);	
			break;
		case GLFW_KEY_LEFT_SHIFT:
			s_inputStates[eInputType::Key_Shift] = GetKeyState(anAction);
			break;
		}
	}

	void InputHandler::CursorCallback(GLFWwindow* aWindow, double xPos, double yPos)
	{
		s_mousePosition.x = xPos;
		s_mousePosition.y = yPos;
	}

	void InputHandler::MouseButtonCallback(GLFWwindow* window, int aButton, int anAction, int someMods)
	{
		if (aButton == GLFW_MOUSE_BUTTON_LEFT)
		{
			s_inputStates[eInputType::Mouse_LeftBtn] = GetKeyState(anAction);
		}
		if (aButton == GLFW_MOUSE_BUTTON_RIGHT)
		{
			s_inputStates[eInputType::Mouse_RightBtn] = GetKeyState(anAction);
		}
	}

	void InputHandler::MapCommand(eInputType anInput, Command* aCommand)
	{
		//s_mappedCommands[anInput] = std::move(aCommand);
		s_mappedCommands.insert_or_assign(anInput, aCommand); 
	}

	bool InputHandler::IsKeyPressed(eInputType anInput)
	{
		return s_inputStates[anInput] == eInputState::Press;
	}

	bool InputHandler::IsKeyHeld(eInputType anInput)
	{
		return s_inputStates[anInput] == eInputState::Repeat;
	}

	bool InputHandler::IsKeyReleased(eInputType anInput)
	{
		return s_inputStates[anInput] == eInputState::Release;
	}

	glm::vec2 InputHandler::GetMousePosition()
	{
		return s_mousePosition;
	}

	eInputState	InputHandler::GetKeyState(int anAction)
	{
		// if anAction == GLFW_PRESS ...

		static std::array<eInputState, 3> possibleInputStates{ eInputState::Release, eInputState::Press, eInputState::Repeat };	// Make member?? make map??
		
		assert(anAction >= 0 && anAction <= 2);
		return possibleInputStates[anAction];
	}

	bool InputHandler::IsCommandMapped(eInputType anInput) const
	{
		return s_mappedCommands.contains(anInput);
	}

	void InputHandler::SendMessage(eInputType anInput)
	{
		if (IsCommandMapped(anInput))
		{
			//Dispatcher::GetInstance().AddEvent<KeyEvent>()
		}
	}
}