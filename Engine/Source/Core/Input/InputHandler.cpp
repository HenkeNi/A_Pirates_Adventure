#include "Pch.h"
#include "InputHandler.h"
#include <GLFW/glfw3.h> 

#include "ServiceLocator/ServiceLocator.h"
#include "Platform/Window/Window.h"

namespace Hi_Engine
{
	std::unordered_map<eKey, eInputState>		InputHandler::s_keyStates;
	std::unordered_map<eMouseBtn, eInputState>	InputHandler::s_mouseButtonStates;
	FVector2									InputHandler::s_mousePosition;
	float										InputHandler::s_scrollOffset;
	GLFWcursor*									InputHandler::s_customCursor = nullptr;


	InputHandler::InputHandler(int initOrder)
		: Module{ initOrder }
	{
	}

	InputHandler::~InputHandler()
	{
		if (s_customCursor)
			glfwDestroyCursor(s_customCursor);
	}

	bool InputHandler::Init()
	{
		if (auto* window = ServiceLocator::GetWindow().lock()->GetWindow())
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		return true;

		//// TODO, custom function? Use image form resource holder?
		//GLFWimage image;
 	//	image.pixels = stbi_load("../Game/Assets/Textures/Icons/arrow-cursor.png", &image.width, &image.height, 0, 4);

		//if (image.pixels)
		//{
		//	//if (s_customCursor = glfwCreateCursor(&image, image.width, image.height))
		//	if (s_customCursor = glfwCreateCursor(&image, 0, 0))
		//	{
		//		if (auto* window = ServiceLocator::GetWindow().lock()->GetWindow())
		//			glfwSetCursor(window, s_customCursor);
		//	}

		//	stbi_image_free(image.pixels);
		//	return true;
		//}
		//else
		//{
		//	const char* errorReason = stbi_failure_reason();  // Get the reason for failure
		//	std::cerr << "Failed to load image: " << errorReason << std::endl;
		//}

		//return false;
	}

	void InputHandler::ProcessInput()
	{
		glfwPollEvents();

		// TODO: save previous frame's key status?!
		InputEvent* inputEvent			= new InputEvent;  // TODO: wrap in a class?!
		inputEvent->m_keyStates			= s_keyStates;
		inputEvent->m_mouseButtonStates = s_mouseButtonStates;
		inputEvent->m_mousePosition		= s_mousePosition;
		EventDispatcher::GetInstance().SendEventInstantly(inputEvent);

		delete inputEvent; 
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
		// Scrolling towards is negative, away is positive, no scrolling == 0
		s_scrollOffset = (float)yoffset; 
	}

	void InputHandler::CursorCallback(GLFWwindow* window, double xPos, double yPos)
	{
		s_mousePosition = { (float)xPos, (float)yPos };
	}

	FVector2 InputHandler::GetMousePosition()
	{
		return s_mousePosition;
	}

	float InputHandler::GetScrollOffset()
	{
		return s_scrollOffset;
	}

	bool InputHandler::IsMouseButtonPressed(eMouseBtn btn)
	{
		return s_mouseButtonStates[btn] == eInputState::Input_Press;
	}

	bool InputHandler::IsKeyPressed(eKey key)
	{
		return s_keyStates[key] == eInputState::Input_Press;
	}

	bool InputHandler::IsKeyHeld(eKey key)
	{
		return s_keyStates[key] == eInputState::Input_Repeat;
	}

	bool InputHandler::IsKeyReleased(eKey key)
	{
		return s_keyStates[key] == eInputState::Input_Release;
	}
}