#pragma once
#include "Messaging/Listener/EventListener.h"

namespace Hi_Engine
{
	class Application;
	class Timer;

	class Engine : public EventListener
	{
	public:
		Engine(Application* app);
		~Engine();

		void HandleEvent(class TerminationEvent& event) override;

		bool Init();
		void Shutdown();
		void Run();

		// static AudioController& GetAudioController();
		static Timer& GetTimer();

	private:
		bool			CreateWindow();		

		//ResourceHolder<Texture2D> m_textureHolder;	// static? in Game?
		//ResourceHolder<GLSLShader>		m_shaderHolder;

		std::unique_ptr<class InputHandler>		m_inputHandler = nullptr;
		std::unique_ptr<class Renderer>			m_renderer = nullptr;
		std::unique_ptr<class Window>			m_window = nullptr;
		std::unique_ptr<class AudioController>	m_audioController = nullptr;

		Application*	m_application;
		bool m_isRunning;
	};
}