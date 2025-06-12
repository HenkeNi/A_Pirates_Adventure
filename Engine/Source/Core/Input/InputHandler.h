#pragma once
#include "InputTypes.h"
#include "../Service/IService.h"

#include "../Math/Vectors/Vector.hpp" // REMOVE?

struct GLFWwindow;
struct GLFWcursor;

// TODO; add cursor struct; contains images and pointer to cursor?

namespace Hi_Engine
{
	// CONSIDER; changing name to InputService
	// Don't have static functions?

	// or just InputHandler?
	class IInputHandler : public IService 
	{};

	// GFWLInputHandler? 
	class InputHandler : public IInputHandler // TODO; make non static?
	{
	public:
		InputHandler();
		~InputHandler();

		// bool Initialize() override; -> best way to call and pass in window?
		void ProcessInput();
		void Reset();

		static GLFWcursor* SetCustomCursor(GLFWwindow* window, const char* iconPath);
		static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void CursorCallback(GLFWwindow* window, double xPos, double yPos);

		static FVector2 GetMousePosition();
		static float GetScrollOffset();

		static bool IsMouseButtonPressed(eMouseBtn btn);
		static bool IsKeyPressed(eKey key);
		static bool IsKeyHeld(eKey key);
		static bool IsKeyReleased(eKey key);

	private:	
		inline static std::unordered_map<eKey, eInputState> s_keyStates;
		inline static std::unordered_map<eMouseBtn, eInputState> s_mouseButtonStates;
		inline static FVector2 s_mousePosition;
		inline static float s_scrollOffset;
		inline static GLFWcursor* s_customCursor;
	};
}