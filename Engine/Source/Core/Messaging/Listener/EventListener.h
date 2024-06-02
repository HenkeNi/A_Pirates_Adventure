#pragma once

namespace Hi_Engine
{
	class EventListener
	{
	public:
		virtual void HandleEvent(class BaseEvent& event)		{};
		virtual void HandleEvent(class TerminationEvent& event)	{};
		virtual void HandleEvent(class WindowEvent& event)		{};
		//virtual void HandleEvent(KeyEvent& anEvent)		{};
		//virtual void HandleEvent(MouseEvent& anEvent)		{};
		virtual void HandleEvent(class InputEvent& event)		{};
		virtual void HandleEvent(class RenderEvent& event)		{};
		virtual void HandleEvent(class TextRenderEvent& event)	{};
		virtual void HandleEvent(class BatchRenderEvent& event)	{};
		virtual void HandleEvent(class PlaySoundEvent& event)	{};
		virtual void HandleEvent(class StopSoundEvent& event)	{};
		//virtual void HandleEvent(RenderSpriteEvent& event)	{};
	};
}