#pragma once
#include "Audio/AudioManager.h"
#include "Input/InputHandler.h"
#include "Window/Window.h"


namespace Hi_Engine
{
	class Application;
	
	class Engine
	{
	public:
		Engine(Application* anApp);
		~Engine();

		bool Init();
		void GameLoop();
		void Shutdown();
		bool IsRunning()		const;
		
	private:
		void SetupRendering(); 
		bool CreateWindow();		

		InputHandler	m_inputHandler;
		Window			m_window;
		AudioManager	m_audioManager;
		Application*	m_application;
		bool			m_isRunning;
	};
}