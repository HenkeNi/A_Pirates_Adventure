	#include "Pch.h"
#include "InputHandler.h"
#include "Messaging/Dispatcher/Dispatcher.h"
#include "Messaging/Events/SystemEvents/SystemEvents.h"


namespace Hi_Engine
{
	std::unordered_map<eKey, eInputState>		InputHandler::s_keyStates;
	std::unordered_map<eMouseBtn, eInputState>	InputHandler::s_mouseButtonStates;
	glm::vec2									InputHandler::s_mousePosition;

	InputHandler::InputHandler()
	{
	}

	InputHandler::~InputHandler()
	{
	}

	void InputHandler::Init(GLFWwindow* aWindow)
	{
		m_window = aWindow;

		glfwSetKeyCallback(aWindow, InputHandler::KeyCallback);
		glfwSetCursorPosCallback(aWindow, InputHandler::CursorCallback);
		glfwSetMouseButtonCallback(aWindow, InputHandler::MouseButtonCallback);
	}

	void InputHandler::ProcessInput()
	{
		// TODO: save previous frame's key status?!

		Dispatcher::GetInstance().AddEvent<InputEvent>(s_keyStates, s_mouseButtonStates, s_mousePosition);
	}

	void InputHandler::KeyCallback(GLFWwindow* aWindow, int aKey, int aScanCode, int anAction, int someMods)
	{
		s_keyStates.insert_or_assign((eKey)aKey, (eInputState)anAction);
	}

	void InputHandler::MouseButtonCallback(GLFWwindow* window, int aButton, int anAction, int someMods)
	{
		s_mouseButtonStates.insert_or_assign((eMouseBtn)aButton, (eInputState)anAction);
	}

	void InputHandler::CursorCallback(GLFWwindow* aWindow, double xPos, double yPos)
	{
		s_mousePosition = { xPos, yPos };
	}

	glm::vec2 InputHandler::GetMousePosition()
	{
		return s_mousePosition;
	}

	bool InputHandler::IsKeyPressed(eKey aKey)
	{
		return s_keyStates[aKey] == eInputState::Press;
	}

	bool InputHandler::IsKeyHeld(eKey aKey)
	{
		return s_keyStates[aKey] == eInputState::Repeat;
	}

	bool InputHandler::IsKeyReleased(eKey aKey)
	{
		return s_keyStates[aKey] == eInputState::Release;
	}
}