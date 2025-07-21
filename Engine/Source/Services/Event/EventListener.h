#pragma once

namespace Hi_Engine
{
	/*class EventListener
	{
	public:
		virtual ~EventListener() = default;

		template<typename T>
		void OnEvent(T& event) {}
	};*/


	class EventListener
	{
	public:
		virtual ~EventListener() = default;

		virtual void OnEvent(class BaseEvent& event)			{};
		virtual void OnEvent(class TerminationEvent& event)		{};
		virtual void OnEvent(class WindowEvent& event)			{};
		//virtual void OnEvent(KeyEvent& anEvent)				{};
		//virtual void OnEvent(MouseEvent& anEvent)				{};
		virtual void OnEvent(class InputEvent& event)			{};
		virtual void OnEvent(class RenderEvent& event)			{};
		virtual void OnEvent(class SpriteBatchRequest& event)	{};
		virtual void OnEvent(class TextRenderEvent& event)		{};
		virtual void OnEvent(class BatchRenderEvent& event)		{};
		virtual void OnEvent(class PlaySoundEvent& event)		{};
		virtual void OnEvent(class StopSoundEvent& event)		{};
		virtual void OnEvent(class SetVolumeEvent& event)		{};
		virtual void OnEvent(class CreateImGuiWindowRequest& event)		{};
		virtual void OnEvent(class ServiceEvent& event)		{};
		virtual void OnEvent(class SceneEvent& event)		{};
		//virtual void OnEvent(RenderSpriteEvent& event)		{};

		// name HandleEvent?
	};
}