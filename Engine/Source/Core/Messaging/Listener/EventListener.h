#pragma once


namespace Hi_Engine
{
	class Event;
	class WindowEvent;
	class KeyEvent;
	class MouseEvent;
	class RenderEvent;
	class RenderSpriteEvent;


	class EntityEvent;

	class EventListener
	{
	public:
		virtual void HandleEvent(Event& anEvent)				{};
		virtual void HandleEvent(WindowEvent& anEvent)			{};
		virtual void HandleEvent(KeyEvent& anEvent)				{};
		virtual void HandleEvent(MouseEvent& anEvent)			{};
		virtual void HandleEvent(RenderEvent& anEvent)			{};
		virtual void HandleEvent(RenderSpriteEvent& anEvent)	{};
	};
}