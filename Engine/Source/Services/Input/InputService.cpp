#include "Pch.h"
#include "InputService.h"
#include "Services/Window/WindowService.h"
#include "Services/ServiceRegistry.h"
#include <GLFW/glfw3.h> 
//#include "Registry/RegistryAliases.h"

namespace Hi_Engine
{
	// Forwarders
	void KeyCallbackForwarder(GLFWwindow* window, int key, int scanCode, int action, int mods);

	void MouseButtonCallbackForwarder(GLFWwindow* window, int button, int action, int mods);

	void MouseScrollCallbackForwarder(GLFWwindow* window, double xoffset, double yoffset);

	void CursorCallbackForwarder(GLFWwindow* window, double xPos, double yPos);

	InputService::InputService(std::weak_ptr<EventService> eventService)
		: m_customCursor{ nullptr }, m_eventService{ eventService }, m_scrollOffset{ 0.f }
	{
	}

	InputService::~InputService()
	{
		if (m_customCursor)
			glfwDestroyCursor(m_customCursor);
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

	void InputService::AttachToWindow(GLFWwindow* window)
	{
		glfwSetWindowUserPointer(window, this);

		glfwSetKeyCallback(window, KeyCallbackForwarder);
		glfwSetCursorPosCallback(window, CursorCallbackForwarder);
		glfwSetMouseButtonCallback(window, MouseButtonCallbackForwarder);
		glfwSetScrollCallback(window, MouseScrollCallbackForwarder);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	void InputService::DetachFromWindow(GLFWwindow* window)
	{
		if (window)
		{
			glfwSetKeyCallback(window, nullptr);
			glfwSetCursorPosCallback(window, nullptr);
			glfwSetMouseButtonCallback(window, nullptr);
			glfwSetScrollCallback(window, nullptr);
			glfwSetWindowUserPointer(window, nullptr);
		}
	}

	void InputService::ProcessInput()
	{
		glfwPollEvents();

		//EventDispatcher::GetInstance().AddEvent<InputEvent>(s_keyStates, s_mouseButtonStates, s_mousePosition);
	}

	void InputService::Reset()
	{
		m_scrollOffset = 0.f;
	}

	GLFWcursor* InputService::SetCustomCursor(GLFWwindow* window, const char* iconPath)
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

	void InputService::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		m_keyStates.insert_or_assign((eKey)key, (eInputState)action);
	}

	void InputService::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		m_mouseButtonStates.insert_or_assign((eMouseBtn)button, (eInputState)action);
	}

	void InputService::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		// Negative for scrolling towards, positive for away, zero for no scroll.
		m_scrollOffset = (float)yoffset;
	}

	void InputService::CursorCallback(GLFWwindow* window, double xPos, double yPos)
	{
		m_mousePosition = { (float)xPos, (float)yPos };
	}

	bool InputService::IsMouseButtonPressed(eMouseBtn btn) const
	{
		//return m_mouseButtonStates[btn] == eInputState::Input_Press;
		return m_mouseButtonStates.at(btn) == eInputState::Input_Press;
	}

	bool InputService::IsKeyPressed(eKey key) const
	{
		return m_keyStates.at(key) == eInputState::Input_Press;
	}

	bool InputService::IsKeyHeld(eKey key) const
	{
		return m_keyStates.at(key) == eInputState::Input_Repeat;
	}

	bool InputService::IsKeyReleased(eKey key) const
	{
		return m_keyStates.at(key) == eInputState::Input_Release;
	}


	void KeyCallbackForwarder(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		if (auto* service = static_cast<InputService*>(glfwGetWindowUserPointer(window))) // TODO; check exactly how this works!
			service->KeyCallback(window, key, scanCode, action, mods);
	}

	void MouseButtonCallbackForwarder(GLFWwindow* window, int button, int action, int mods)
	{
		if (auto* service = static_cast<InputService*>(glfwGetWindowUserPointer(window)))
			service->MouseButtonCallback(window, button, action, mods);
	}

	void MouseScrollCallbackForwarder(GLFWwindow* window, double xoffset, double yoffset)
	{
		if (auto* service = static_cast<InputService*>(glfwGetWindowUserPointer(window)))
			service->MouseScrollCallback(window, xoffset, yoffset);
	}

	void CursorCallbackForwarder(GLFWwindow* window, double xPos, double yPos)
	{
		if (auto* service = static_cast<InputService*>(glfwGetWindowUserPointer(window)))
			service->CursorCallback(window, xPos, yPos);
	}
}