#pragma once
#include "../../Data/Enumerations.h"
#include <unordered_map>

struct GLFWwindow;

namespace Hi_Engine
{
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void Init(GLFWwindow* aWindow);
		void ProcessInput();
		void Reset();

		static void KeyCallback(GLFWwindow* aWindow, int aKey, int aScanCode, int anAction, int someMods);
		static void MouseButtonCallback(GLFWwindow* window, int aButton, int anAction, int someMods);
		static void MouseScrollCallback(GLFWwindow* aWindow, double xoffset, double yoffset);
		static void CursorCallback(GLFWwindow* aWindow, double xPos, double yPos);

		static glm::vec2 GetMousePosition();
		static float	GetScrollOffset();

		static bool IsKeyPressed(eKey aKey);
		static bool IsKeyHeld(eKey aKey);
		static bool IsKeyReleased(eKey aKey);

	private:	
		static std::unordered_map<eKey, eInputState> s_keyStates;
		static std::unordered_map<eMouseBtn, eInputState> s_mouseButtonStates;
		static glm::vec2 s_mousePosition;
		static float		s_scrollOffset;
		const GLFWwindow* m_window;
	};
}