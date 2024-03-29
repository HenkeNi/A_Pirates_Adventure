	#include "Pch.h"
#include "InputHandler.h"
#include "Messaging/Dispatcher/Dispatcher.h"
#include "Messaging/Events/SystemEvents/SystemEvents.h"


namespace Hi_Engine
{
	std::unordered_map<eKey, eInputState>		InputHandler::s_keyStates;
	std::unordered_map<eMouseBtn, eInputState>	InputHandler::s_mouseButtonStates;
	glm::vec2									InputHandler::s_mousePosition;
	float										InputHandler::s_scrollOffset;
	//GLFWcursor*									InputHandler::s_customCursor = nullptr;


	InputHandler::InputHandler()
	{
	}

	InputHandler::~InputHandler()
	{
		//glfwDestroyCursor(s_customCursor);
	}

	void InputHandler::Init(GLFWwindow* window)
	{
		m_window = window;

		glfwSetKeyCallback(m_window, InputHandler::KeyCallback);
		glfwSetCursorPosCallback(m_window, InputHandler::CursorCallback);
		glfwSetMouseButtonCallback(m_window, InputHandler::MouseButtonCallback);
		glfwSetScrollCallback(m_window, InputHandler::MouseScrollCallback);
 
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


		//static GLFWimage image;
		//image.width *= 10;
		//image.height *= 10;
		//int width = image.width * 0.5f;
		//image.pixels = stbi_load("../Game/Assets/Textures/arrow-cursor.png", &width, &width, 0, 4);
		//image.pixels = stbi_load("../Game/Assets/Textures/arrow-cursor.png", &image.width, &image.height, 0, 4); // Fix pivot (upper left corner)
		//if (s_customCursor = glfwCreateCursor(&image, 2, -2.5))
			//glfwSetCursor(m_window, s_customCursor);
	}

	void InputHandler::ProcessInput()
	{
		// TODO: save previous frame's key status?!
		InputEvent* inputEvent			= new InputEvent;  // TODO: wrap in a class?!
		inputEvent->m_keyStates			= s_keyStates;
		inputEvent->m_mouseButtonStates = s_mouseButtonStates;
		inputEvent->m_mousePosition		= s_mousePosition;
		Dispatcher::GetInstance().SendEventInstantly(inputEvent);

		delete inputEvent; 

		// TEMP
		//s_scrollOffset = 0.f; -> resets it before it can be used?? -> wonky solution; reset it when calling GetMouseScroll()?!

		//Dispatcher::GetInstance().SendEventInstantly<InputEvent>(s_keyStates, s_mouseButtonStates, s_mousePosition);
		//Dispatcher::GetInstance().AddEvent<InputEvent>(s_keyStates, s_mouseButtonStates, s_mousePosition);
	}

	void InputHandler::Reset()
	{
		s_scrollOffset = 0.f;
	}

	void InputHandler::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		s_keyStates.insert_or_assign((eKey)key, (eInputState)action);
	}

	void InputHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		s_mouseButtonStates.insert_or_assign((eMouseBtn)button, (eInputState)action);
	}

	void InputHandler::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		s_scrollOffset = (float)yoffset; // down (towrads is negative) up (is positive) -> no scrolling == 0
	}

	void InputHandler::CursorCallback(GLFWwindow* window, double xPos, double yPos)
	{
		s_mousePosition = { xPos, yPos };
	}

	glm::vec2 InputHandler::GetMousePosition()
	{
		return s_mousePosition;
	}

	float InputHandler::GetScrollOffset()
	{
		return s_scrollOffset;
	}

	bool InputHandler::IsMouseButtonPressed(eMouseBtn btn)
	{
		return s_mouseButtonStates[btn] == eInputState::Press;
	}

	bool InputHandler::IsKeyPressed(eKey key)
	{
		return s_keyStates[key] == eInputState::Press;
	}

	bool InputHandler::IsKeyHeld(eKey key)
	{
		return s_keyStates[key] == eInputState::Repeat;
	}

	bool InputHandler::IsKeyReleased(eKey key)
	{
		return s_keyStates[key] == eInputState::Release;
	}
}