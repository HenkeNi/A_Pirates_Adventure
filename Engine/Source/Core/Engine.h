#pragma once
#include "Input/InputHandler.h"
#include "Window/Window.h"
#include "Utility/Time/Timer.h"

namespace CU = CommonUtilities;

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

		InputHandler	m_inputHandler;
		Window			m_window;
		CU::Timer		m_timer;
		Application*	m_application;

		bool			m_isRunning;

		// Graphics m_graphics??
		// Physics m_physics?? or just collisionManager??
		// AI ??
		// Renderer
		// AudioManager?
		// CollisionManager?
	};


	Application* CreateApplication();
}