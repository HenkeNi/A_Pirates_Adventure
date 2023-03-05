#pragma once
#include "Audio/AudioManager.h"
#include "Input/InputHandler.h"
#include "Window/Window.h"
#include "Utility/Time/Timer.h"


namespace Hi_Engine
{
	class Application;
	
	class Engine
	{
	public:
		Engine();

		bool Init();
		bool IsRunning() const;

		void ProcessInput();
		void Update();
		void LateUpdate();
		void Draw();
		void Shutdown();

	private:
		bool SetupWindow();
		void MapControlls();

		InputHandler	m_inputHandler;
		Window			m_window;
		Timer			m_timer;
		AudioManager	m_audioManager;
		Application*	m_application;

		bool			m_isRunning;




		// Graphics m_graphics?? or make Asset/Resource-Manager a singleton
		// Physics m_physics?? or just collisionManager??
		// AI ??
		// Renderer
		// AudioManager?
		// CollisionManager?
	};


	Application* CreateApplication();
}