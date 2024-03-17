#pragma once


namespace Hi_Engine
{
	//class Event;
	class BaseEvent;
	class TerminationEvent;
	class WindowEvent;
	class InputEvent;
//	class KeyEvent;
//	class MouseEvent;
	class RenderEvent;
	class RenderSpriteEvent;


	class EntityEvent;

	class EventListener
	{
	public:
		virtual void HandleEvent(BaseEvent& event)			{};
		virtual void HandleEvent(TerminationEvent& event)		{};
		virtual void HandleEvent(WindowEvent& event)			{};
		//virtual void HandleEvent(KeyEvent& anEvent)				{};
		//virtual void HandleEvent(MouseEvent& anEvent)			{};
		virtual void HandleEvent(InputEvent& event)			{};
		virtual void HandleEvent(RenderEvent& event)			{};
		virtual void HandleEvent(RenderSpriteEvent& event)	{};
	};
}