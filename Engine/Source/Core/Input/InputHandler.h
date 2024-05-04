#pragma once

enum class eKey;
struct GLFWwindow;

namespace Hi_Engine
{
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void Init(GLFWwindow* window);
		void ProcessInput();
		void Reset();

		static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void CursorCallback(GLFWwindow* window, double xPos, double yPos);

		static glm::vec2 GetMousePosition();
		static float	 GetScrollOffset();

		static bool IsMouseButtonPressed(eMouseBtn btn);
		static bool IsKeyPressed(eKey key);
		static bool IsKeyHeld(eKey key);
		static bool IsKeyReleased(eKey key);

	private:	
		static std::unordered_map<eKey, eInputState> s_keyStates;
		static std::unordered_map<eMouseBtn, eInputState> s_mouseButtonStates;
		static glm::vec2	s_mousePosition;
		static float		s_scrollOffset;
		// static GLFWcursor*	s_customCursor;
	};
}