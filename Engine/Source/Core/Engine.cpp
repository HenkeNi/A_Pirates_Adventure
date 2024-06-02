#include "Pch.h"
#include "Engine.h"
#include "Application/Application.h"
#include "Resources/ResourceHolder.hpp"
#include "Rendering/Text/Renderer/TextRenderer.h"
#include "ServiceLocator/ServiceLocator.h"
#include "Rendering/Renderer/Renderer.h"
#include "Audio/AudioController.h"
#include "Input/InputHandler.h"
#include "Window/Window.h"
#include "../Utility/Time/Timer.h"
#include <GLFW/glfw3.h> 


namespace Hi_Engine
{
	void ErrorCallbackGLFW(int error, const char* description)
	{
		std::cerr << "GLFW Error [" << error << "]: " << description << "\n";
	}

	Engine::Engine(Application& app)
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
		glfwSetErrorCallback(ErrorCallbackGLFW);

		if (!m_moduleManager.Init())
			return false;

	/*	GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			std::cerr << "GLEW Error: " << glewGetErrorString(error) << std::endl;
			return false;
		}*/

		LoadResources(); // Do in LoadModules?
		m_moduleManager.LoadModules();

		//ConfigureRenderStates();
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

	
		m_application.OnCreate(); 


		// Load default resources (do in Desrializer)
		//auto renderer = m_moduleManager.GetModule<Renderer>();
		//renderer.lock()->SetShader(&ResourceHolder<GLSLShader>::GetInstance().GetResource("sprite_batch")); // Rename default_sprite_bact
		//m_renderer->SetShader(&ResourceHolder<GLSLShader>::GetInstance().GetResource("sprite_batch")); // Rename default_sprite_bact

		
		//ServiceLocator::Register(audioController); // FIX!
		//ServiceLocator::Register(&m_audioController);
		
		return (m_isRunning = true);
	}

	void Engine::Shutdown()
	{
		m_application.OnDestroy();
		m_moduleManager.Shutdown();
	}

	void Engine::Run()
	{
		//assert(m_application && "Failed to launch application");
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
			m_application.OnUpdate(deltaTime);
			m_application.OnLateUpdate(deltaTime);

			/* - Clear screen - */
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // put in renderer

			/* - Render - */
			m_application.OnDraw();

			if (renderer)
				renderer->ProcessCommands();

			if (window)
				window->SwapBuffers();

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
		m_moduleManager.RegisterModule<Window>(1);
		m_moduleManager.RegisterModule<Renderer>(2);
		m_moduleManager.RegisterModule<TextRenderer>(3);
		m_moduleManager.RegisterModule<InputHandler>(4);
		m_moduleManager.RegisterModule<AudioController>(5);
	}
	void Engine::LoadResources()
	{
		ResourceHolder<GLSLShader>::GetInstance().LoadResources("../Engine/Assets/Json/Resources/Shaders.json");
	}
}