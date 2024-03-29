#pragma once
#include "Audio/AudioManager.h"
#include "Rendering/Renderer/Renderer.h"
#include "Input/InputHandler.h"
#include "Window/Window.h"


namespace Hi_Engine
{
	class Application;
	class Timer;

	class Engine : public EventListener
	{
	public:
		Engine(Application* app);
		~Engine();

		void HandleEvent(TerminationEvent& event) override;

		bool Init();
		void Shutdown();
		void GameLoop();
		bool IsRunning() const;

		static Timer& GetTimer();

	private:
		bool			CreateWindow();		

		//ResourceHolder<Texture2D> m_textureHolder;	// static? in Game?
		//ResourceHolder<Shader>		m_shaderHolder;

		InputHandler	m_inputHandler;
		AudioManager	m_audioManager;
		Application*	m_application;
		Renderer		m_renderer;
		Window			m_window;
		bool			m_isRunning;
	};
}