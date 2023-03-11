#pragma once
#include "../Event.h"
#include "Data/Enumerations.h"


namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class WindowEvent : public Event
	{
	public:
		WindowEvent(eWindowEvent aType); // Overload new operatp`?? placement new??

		void Dispatch(EventListener& aListener) override;

		eWindowEvent GetEventType() const;

	private:
		eWindowEvent		m_eventType;
		CU::Vector2<unsigned>	m_windowSize;
	};



	class KeyEvent : public Event
	{
	public:
		KeyEvent();

		void	Dispatch(EventListener& aListener) override;

	private:
		eKeyState m_keyState;
	};



	class MouseEvent : public Event
	{
		// OR KEy mesage and mouse messag (current pos, last pos, maybe keypressed as well (rather tha having to listen for a key)) or combine it all and send a Input Event?
		// Maybe store relevant keys here as well??
	public:
		MouseEvent();

		void	Dispatch(EventListener& aListener) override;

	private:
		// Store under struct MouseData??
		CU::Vector2<unsigned>	m_currentMousePos, m_previousMousePos;
		bool					m_leftMouseCliked; // STATE?
	};

}