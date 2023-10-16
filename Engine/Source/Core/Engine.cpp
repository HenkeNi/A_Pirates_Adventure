#include "Pch.h"
#include "Engine.h"
#include "Application.h"
#include "FileIO/FileSystem.h"
#include "FileIO/Parsers/WindowParser.h"
#include "Resources/ResourceHolder.hpp"

#include "Rendering/Renderer/TextRenderer/TextRenderer.h"
#include "../Utility/Time/Timer.h"
#include "../Messaging/Dispatcher/Dispatcher.h"


namespace Hi_Engine
{
	Engine::Engine(Application* anApp)
		: m_application{ anApp }, m_isRunning{ false }
	{
	}

	Engine::~Engine()
	{
	}

	bool Engine::Init()
	{
		if (!CreateWindow() || glewInit() != GLEW_OK || !m_application)
			return false;

		//ConfigureRenderStates();
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		m_inputHandler.Init(m_window.m_window);

		// REMOVE...
		TextRenderer::GetInstance().Init();

		// TEMP
		m_renderer.Init();
		m_renderer.SetRenderTarget(&m_window);

		m_application->OnCreate(); 


		m_renderer.SetShader(&ResourceHolder<Shader>::GetInstance().GetResource("sprite_batch")); // Rename default_sprite_bact

		
		return (m_isRunning = true);
	}

	void Engine::Shutdown()
	{
		if (m_window.IsOpen())
			m_window.Close();

		m_renderer.Shutdown();

		TextRenderer::GetInstance().Shutdown();

		if (m_application)
		{
			m_application->OnDestroy();
			delete m_application;
		}
	}

	void Engine::GameLoop()
	{
		assert(m_application && "Failed to launch application");
		Timer& timer = GetTimer();
		//Timer timer;

		while (IsRunning())	// Todo, use enum for GameState instead? !GameState::EXIT
		{
 			timer.Update();
			const float deltaTime = timer.GetDeltaTime();

			Dispatcher::GetInstance().DispatchEvents();

			/* - Process input - */
			m_window.PollEvents();					
			m_inputHandler.ProcessInput();

			/* - Update - */
			m_application->OnUpdate(deltaTime);
			m_application->OnLateUpdate(deltaTime);

			/* - Render - */
			m_renderer.BeginFrame();
			m_application->OnDraw();
			m_renderer.EndFrame();	// Always call Display in EndFrame?
	
			m_window.SetTitle("Fps: " + std::to_string((int)timer.GetAverageFPS())); // TODO; Get Draw calls...
		}
	}
		
	bool Engine::IsRunning() const
	{
		return m_window.IsOpen() && m_isRunning;
	}

	Timer& Engine::GetTimer()
	{
		static Timer timer;
		return timer;
	}

	bool Engine::CreateWindow()
	{
		auto windowData = FileSystem::ParseJson<WindowParser, WindowData>("../Engine/Assets/Json/Window/Window.json");
		return m_window.Init(windowData);
	}

	//void Engine::ConfigureRenderStates()
	//{
	//	glEnable(GL_DEPTH_TEST);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			
	//	glEnable(GL_BLEND);
	//}
}