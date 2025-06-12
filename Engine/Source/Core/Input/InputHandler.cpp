#include "Pch.h"
#include "InputHandler.h"
#include "Platform/Window/Window.h"
#include <GLFW/glfw3.h> 

namespace Hi_Engine
{
	InputHandler::InputHandler()
	{
		s_customCursor = nullptr;
	}

	InputHandler::~InputHandler()
	{
		if (s_customCursor)
			glfwDestroyCursor(s_customCursor);
	}

	//bool InputHandler::Initialize()
	//{
	//	if (auto windowModule = m_moduleManager.GetModule<Window>().lock())
	//	{
	//		// glfwSetInputMode(windowModule->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	//	
	//		// amybe move some of this logic to window class?
	//		if (auto* window = windowModule->GetWindow())
	//		{
	//			if (s_customCursor = SetCustomCursor(window, "../Game/Assets/Textures/Icons/arrow-cursor.png"))
	//				glfwSetCursor(window, s_customCursor);
	//			else
	//				Logger::LogWarning("InputHandler::Init - Failed to create custom cursor!");  
	//		}
	//	}

	//	return true;
	//}

	void InputHandler::ProcessInput()
	{
		glfwPollEvents();

		EventDispatcher::GetInstance().AddEvent<InputEvent>(s_keyStates, s_mouseButtonStates, s_mousePosition);
	}

	void InputHandler::Reset()
	{
		s_scrollOffset = 0.f;
	}

	GLFWcursor* InputHandler::SetCustomCursor(GLFWwindow* window, const char* iconPath)
	{
		// TODO: use image form resource holder?

		GLFWimage image;
		image.pixels = stbi_load(iconPath, &image.width, &image.height, 0, 4);

		if (!image.pixels)
		{
			const char* errorReason = stbi_failure_reason();
			Logger::LogError("InputHandler::SetCustomIcon - Failed to load icon! Reason: " + std::string(errorReason));
			
			return nullptr;
		}

		auto* cursor = glfwCreateCursor(&image, image.width, image.height);
		stbi_image_free(image.pixels);

		return cursor;
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
		// Negative for scrolling towards, positive for away, zero for no scroll.
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