#pragma once


namespace Hi_Engine
{
	class Event;
	class WindowEvent;
	class KeyEvent;
	class MouseEvent;

	class EventListener
	{
	public:
		virtual void HandleEvent(Event& anEvent)		{};
		virtual void HandleEvent(WindowEvent& anEvent)	{};
		virtual void HandleEvent(KeyEvent& anEvent)		{};
		virtual void HandleEvent(MouseEvent& anEvent)	{};
	};
}