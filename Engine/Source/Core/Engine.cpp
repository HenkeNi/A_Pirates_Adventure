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
#include "ImGui/ImGuiManager.h"
#include "../Utility/Time/Timer.h"
#include <GLFW/glfw3.h> 
#include "ServiceLocator/ServiceLocator.h" /// ?
#include "Noise/NoiseGenerator.h"


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

		LoadResources(); // Do in LoadModules?
		m_moduleManager.LoadModules();

		NoiseGenerator::Init();

		m_application.OnCreate(); 
		
		return (m_isRunning = true);
	}

	void Engine::Shutdown()
	{
		m_application.OnDestroy();
		m_moduleManager.Shutdown();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Engine::Run()
	{
		//assert(m_application && "Failed to launch application");
		Timer& timer = GetTimer();
		//Timer timer;
		
		auto inputHandler = m_moduleManager.GetModule<InputHandler>().lock();
		auto renderer = m_moduleManager.GetModule<Renderer>().lock();
		auto window = m_moduleManager.GetModule<Window>().lock();
		auto editor = m_moduleManager.GetModule<ImGuiManager>().lock();

		auto textRenderer = m_moduleManager.GetModule<TextRenderer>().lock();

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

			if (editor)
				editor->BeginFrame();

			if (renderer)
				renderer->ProcessCommands();
			//if (textRenderer)
			//	textRenderer->ProcessQueue();

			if (editor)
				editor->Render();

			if (window)
				window->SwapBuffers();

			if (inputHandler)
				inputHandler->Reset();
			
#ifdef DEBUG
			if (window)
				window->SetTitle("Fps: " + std::to_string((int)timer.GetAverageFPS())); // TODO; Get Draw calls...
#endif 
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

#ifdef DEBUG
		m_moduleManager.RegisterModule<ImGuiManager>(6);
#endif

		ServiceLocator::Register(m_moduleManager.GetModule<Window>());
	}

	void Engine::LoadResources()
	{
		ResourceHolder<GLSLShader>::GetInstance().LoadResources("../Engine/Assets/Json/Resources/Shaders.json");
	}
}