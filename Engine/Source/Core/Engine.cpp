#include "Pch.h"
#include "Engine.h"
#include "Application/Application.h"
#include <GLFW/glfw3.h> 

#include "Resources/ResourceHolder.hpp"
//#include "Messaging/Dispatcher/Dispatcher.h"
#include "../Utility/Time/Timer.h"
#include "Rendering/Text/Renderer/TextRenderer.h"
#include "ServiceLocator/ServiceLocator.h"
#include "Utility/UtilityFunctions.hpp"
#include "Rendering/Renderer/Renderer.h"
#include "Input/InputHandler.h"
#include "Audio/AudioController.h"
#include "Window/Window.h"

namespace Hi_Engine
{
	Engine::Engine(Application* app)
		: m_application{ app }, m_isRunning{ false }
	{
		Dispatcher::GetInstance().Subscribe(this);
		RegisterModules();
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

		
		auto audioController = m_moduleManager.GetModule<AudioController>();
		auto renderer = m_moduleManager.GetModule<Renderer>();
		auto window = m_moduleManager.GetModule<Window>();
		auto inputHandler = m_moduleManager.GetModule<InputHandler>();
			
		audioController.lock()->Init();
		inputHandler.lock()->Init(window.lock()->m_window);
		renderer.lock()->Init();



		//m_inputHandler->Init(m_window->m_window);

		//m_window.SetIcon("../Game/Assets/Textures/Icons/pirate_flag_icon.png"); // TODO: read from windows file

		// REMOVE...
		TextRenderer::GetInstance().Init();

		// TEMP
		//m_renderer->Init();
		//m_renderer.SetRenderTarget(&m_window);

		//m_audioController->Init();

		m_application->OnCreate(); 


		// Load default resources 
		renderer.lock()->SetShader(&ResourceHolder<GLSLShader>::GetInstance().GetResource("sprite_batch")); // Rename default_sprite_bact
		//m_renderer->SetShader(&ResourceHolder<GLSLShader>::GetInstance().GetResource("sprite_batch")); // Rename default_sprite_bact

		
		//ServiceLocator::Register(audioController); // FIX!
		//ServiceLocator::Register(&m_audioController);
		
		return (m_isRunning = true);
	}

	void Engine::Shutdown()
	{
		if (m_application)
		{
			m_application->OnDestroy();
			delete m_application;
		}

		// shutdown module manager
		m_moduleManager.GetModule<Window>().lock()->Shutdown();
		m_moduleManager.GetModule<AudioController>().lock()->Shutdown();
		m_moduleManager.GetModule<Renderer>().lock()->Shutdown();
		auto inputHandler = m_moduleManager.GetModule<InputHandler>();


		//m_window->Shutdown();
		//m_renderer->Shutdown();
		TextRenderer::GetInstance().Shutdown();

		//m_audioController->Shutdown();
	}

	void Engine::Run()
	{
		assert(m_application && "Failed to launch application");
		Timer& timer = GetTimer();
		//Timer timer;
		
		auto inputHandler = m_moduleManager.GetModule<InputHandler>().lock();
		auto renderer = m_moduleManager.GetModule<Renderer>().lock();
		auto window = m_moduleManager.GetModule<Window>().lock();

		while (m_isRunning)	// Todo, use enum for GameState instead? !GameState::EXIT or call function in Application? ShouldRun()?
		{
 			timer.Update();
			const float deltaTime = timer.GetDeltaTime();

			Dispatcher::GetInstance().DispatchEvents();

			/* - Process input - */
			if (inputHandler)
				inputHandler->ProcessInput();

			/* - Update - */
			m_application->OnUpdate(deltaTime);
			m_application->OnLateUpdate(deltaTime);

			/* - Clear screen - */
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // put in renderer

			/* - Render - */
			m_application->OnDraw();

			if (renderer)
				renderer->ProcessCommands();

			if (window)
				glfwSwapBuffers(window->m_window); // window swap buffers

			if (inputHandler)
				inputHandler->Reset();
			
			if (window)
				window->SetTitle("Fps: " + std::to_string((int)timer.GetAverageFPS())); // TODO; Get Draw calls...
		}
	}
		
	Timer& Engine::GetTimer()
	{
		static Timer timer;
		return timer;
	}

	void Engine::RegisterModules()
	{
		m_moduleManager.RegisterModule<InputHandler>();
		m_moduleManager.RegisterModule<Renderer>();
		m_moduleManager.RegisterModule<Window>();
		m_moduleManager.RegisterModule<AudioController>();
	}

	bool Engine::CreateWindow() // FIX?!
	{
		bool success = false;

		auto document = ParseDocument("../Engine/Assets/Json/Window/Window.json");
		auto json = ParseJson(document.GetObj());

		auto values = std::any_cast<std::unordered_map<std::string, std::any>>(json);
		auto size = std::any_cast<std::unordered_map<std::string, std::any>>(values.at("size"));

		std::string windowName = std::any_cast<std::string>(values.at("name"));
		std::string iconPath = std::any_cast<std::string>(values.at("icon_path"));
		IVector2 windowSize = { std::any_cast<int>(size.at("width")), std::any_cast<int>(size.at("height")) };
		
		if (m_moduleManager.GetModule<Window>().lock()->Init(windowSize, windowName))
		{
			m_moduleManager.GetModule<Window>().lock()->SetIcon(iconPath);
			success = true;
		}

		return success;
	}
}