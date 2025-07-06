#pragma once
#include "InputTypes.h"
#include "../IService.h"
#include "Math/Vectors/Vector.hpp" // remoev

struct GLFWwindow;
struct GLFWcursor;

// TODO; add cursor struct; contains images and pointer to cursor?

namespace Hi_Engine
{
	// Consider implementing IInputService -> GLFWInputService (if flexibility)

	class EventService;

	class InputService : public IService
	{
	public:
		InputService(std::weak_ptr<EventService> eventService);
		~InputService();

		// Delete copy / move?

		// register keys??

		void AttachToWindow(GLFWwindow* window); // needs to be called! or better as an event?
		void DetachFromWindow(GLFWwindow* window);

		void ProcessInput();
		void Reset();

		GLFWcursor* SetCustomCursor(GLFWwindow* window, const char* iconPath);

		void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods); // what are these used for??
		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		void CursorCallback(GLFWwindow* window, double xPos, double yPos);

		[[nodiscard]] inline const FVector2& GetMousePosition() const { return m_mousePosition; }
		[[nodiscard]] inline float GetScrollOffset() const { return m_scrollOffset; }

		[[nodiscard]] bool IsMouseButtonPressed(eMouseBtn btn) const;

		// combine into GetKeyStatus?
		[[nodiscard]] bool IsKeyPressed(eKey key) const;
		[[nodiscard]] bool IsKeyHeld(eKey key) const;
		[[nodiscard]] bool IsKeyReleased(eKey key) const;

	private:	
		std::unordered_map<eKey, eInputState> m_keyStates;
		std::unordered_map<eMouseBtn, eInputState> m_mouseButtonStates;

		FVector2 m_mousePosition;
		float m_scrollOffset;
		GLFWcursor* m_customCursor;
		std::weak_ptr<EventService> m_eventService;
	};
}