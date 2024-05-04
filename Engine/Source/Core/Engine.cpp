#include "Pch.h"
#include "Engine.h"
#include "Application/Application.h"
#include "FileIO/Parsers/WindowParser.h"
#include "Resources/ResourceHolder.hpp"
#include "Messaging/Dispatcher/Dispatcher.h"
#include "../Utility/Time/Timer.h"
#include "Rendering/Renderer/TextRenderer/TextRenderer.h"
#include "ServiceLocator/ServiceLocator.h"
#include "Utility/UtilityFunctions.hpp"

namespace Hi_Engine
{
	Engine::Engine(Application* app)
		: m_application{ app }, m_isRunning{ false }
	{
		Dispatcher::GetInstance().Subscribe(this);
	}

	Engine::~Engine()
	{
		Dispatcher::GetInstance().Unsubscribe(this);
	}

	void Engine::HandleEvent(TerminationEvent& event)
	{
		m_isRunning = false;
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

		//m_window.SetIcon("../Game/Assets/Textures/Icons/pirate_flag_icon.png"); // TODO: read from windows file

		// REMOVE...
		TextRenderer::GetInstance().Init();

		// TEMP
		m_renderer.Init();
		//m_renderer.SetRenderTarget(&m_window);

		m_audioController.Init();

		m_application->OnCreate(); 


		m_renderer.SetShader(&ResourceHolder<Shader>::GetInstance().GetResource("sprite_batch")); // Rename default_sprite_bact

		
		ServiceLocator::Register(&m_audioController);
		
		return (m_isRunning = true);
	}

	void Engine::Shutdown()
	{
		if (m_application)
		{
			m_application->OnDestroy();
			delete m_application;
		}

		m_window.Shutdown();
		m_renderer.Shutdown();
		TextRenderer::GetInstance().Shutdown();

		m_audioController.Shutdown();
	}

	void Engine::GameLoop()
	{
		assert(m_application && "Failed to launch application");
		Timer& timer = GetTimer();
		//Timer timer;

		while (IsRunning())	// Todo, use enum for GameState instead? !GameState::EXIT or call function in Application? ShouldRun()?
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
			m_window.ClearScreen();
			m_application->OnDraw();
			m_renderer.ProcessCommands(); // NEEDED? Or render when event directly? Maybe wont work when multithreading?
			m_window.SwapBuffers();
			
			m_inputHandler.Reset(); // OR Force user to listen to scroll event??
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

	bool Engine::CreateWindow() // FIX?!
	{
		auto document = ParseDocument("../Engine/Assets/Json/Window/Window.json");
		auto json = ParseJson(document.GetObj());

		auto values = std::any_cast<std::unordered_map<std::string, std::any>>(json);
		auto size = std::any_cast<std::unordered_map<std::string, std::any>>(values.at("size"));

		WindowData data;
		data.WindowName = std::any_cast<std::string>(values.at("name"));
		data.IconPath = std::any_cast<std::string>(values.at("icon_path"));
		data.Size = { std::any_cast<int>(size.at("width")), std::any_cast<int>(size.at("height")) };
		
		return m_window.Init(data);
	}

	//void Engine::ConfigureRenderStates()
	//{
	//	glEnable(GL_DEPTH_TEST);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			
	//	glEnable(GL_BLEND);
	//}
}