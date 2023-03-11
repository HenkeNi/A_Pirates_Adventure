#include "Pch.h"
#include "SystemEvents.h"
#include "../../Listener/EventListener.h"


namespace Hi_Engine
{
#pragma region WINDOW_EVENT

	WindowEvent::WindowEvent(eWindowEvent aType)
		: Event{ ePriority::High }, m_eventType{ aType }
	{
	}

	void WindowEvent::Dispatch(EventListener& aListener)
	{
		aListener.HandleEvent(*this);
	}

	eWindowEvent WindowEvent::GetEventType() const
	{
		return m_eventType;
	}

#pragma endregion WINDOW_EVENT



#pragma region KEY_EVENT

	KeyEvent::KeyEvent()
		: Event{ ePriority::High }
	{
	}

	void KeyEvent::Dispatch(EventListener& aListener)
	{
		aListener.HandleEvent(*this);
	}

#pragma endregion KEY_EVENT



#pragma region MOUSE_EVENT

	MouseEvent::MouseEvent()
		: Event{ ePriority::High }
	{
	}

	void MouseEvent::Dispatch(EventListener& aListener)
	{

	}

#pragma endregion MOUSE_EVENT
}