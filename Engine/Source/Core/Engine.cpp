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
	std::mutex mtx;
	std::condition_variable cv;
	bool ready = false;



	Engine::Engine(Application* anApp)
		: m_application{ anApp }, m_isRunning{ false }, m_isRenderingComplete{ true }
	{
	}

	Engine::~Engine()
	{
	}

	bool Engine::Init()
	{
		assert(m_application && "Not a valid Application!");

		m_renderThread = std::thread(&Engine::Render, this);

		//std::thread renderThread{ &Engine::Render, this }; // Or pass window/renderer with std::ref(m_window), std::ref(m_renderer)
		//renderThread.detach();

		{
			std::unique_lock<std::mutex> lock(mtx);
			cv.wait(lock, [] { return ready; });
		}



		//if (!CreateWindow() || glewInit() != GLEW_OK || !m_application)
		//	return false;
		//
		////ConfigureRenderStates();
		//glEnable(GL_DEPTH_TEST);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_BLEND);

		m_inputHandler.Init(m_window.m_window);

		// REMOVE...
		//TextRenderer::GetInstance().Init();

		// TEMP
		//m_renderer.Init();
		//m_renderer.SetRenderTarget(&m_window);

		m_application->OnCreate(); 


		//m_renderer.SetShader(&ResourceHolder<Shader>::GetInstance().GetResource("sprite_batch")); // Rename default_sprite_bact

		return (m_isRunning = true);
	}

	void Engine::Shutdown()
	{
		if (m_window.IsOpen())
			m_window.Close();

		//m_renderer.Shutdown();
		//TextRenderer::GetInstance().Shutdown();

		if (m_renderThread.joinable())
		{
			m_shouldQuit = true;
			m_cv.notify_one();
			m_renderThread.join();
		}

		if (m_application)
		{
			m_application->OnDestroy();
			delete m_application;
		}
	}

	void Engine::Update()
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
			/*{
				std::lock_guard<std::mutex> lock{ m_mutex };
				m_window.PollEvents();
				m_inputHandler.ProcessInput();
			}*/
			//m_window.PollEvents();
			//m_inputHandler.ProcessInput();

			/* - Update - */
			m_application->OnUpdate(deltaTime);
			m_application->OnLateUpdate(deltaTime);

			/* - Render - */
			{
				std::lock_guard<std::mutex> lock{ m_mutex };
				Dispatcher::GetInstance().SendEventInstantly<ClearBufferEvent>();

				m_application->OnDraw();
				DataReady.store(true);
				m_cv.notify_one();
			}
			
			//m_renderer.BeginFrame();
			// m_application->OnDraw();
			//m_renderer.EndFrame();	// Always call Display in EndFrame?
	
			std::cout << "FPS: " << std::to_string((int)timer.GetAverageFPS()) << "\n";
			//m_window.SetTitle("Fps: " + std::to_string((int)timer.GetAverageFPS()) + " - Draw calls: " + std::to_string(m_renderer.GetRenderStats().TotalDraws)); // TODO; Get Draw calls...
		}
	}
		
	void Engine::Render()
	{
		if (!CreateWindow() || glewInit() != GLEW_OK)
			return;

		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		//Renderer renderer; -> declare in function?
		// Create local renderer here...

		Renderer renderer;

		// Do elsewhere??
		ResourceHolder<Texture2D>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Textures2.json");
		ResourceHolder<Shader>::GetInstance().LoadResources("../Engine/Assets/Json/Resources/Shaders.json");
		ResourceHolder<Font>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Fonts.json");

		{
			std::lock_guard<std::mutex> lock(mtx);
			ready = true;
			cv.notify_one();
		}


		renderer.Init();
		renderer.SetRenderTarget(&m_window);
		renderer.SetShader(&ResourceHolder<Shader>::GetInstance().GetResource("sprite_batch")); // Rename default_sprite_bact
	
		// pass in window??
		while (m_window.IsOpen())	// Dont use window?? use bool?!
		{
			m_window.PollEvents();
			m_inputHandler.ProcessInput();

			std::unique_lock<std::mutex> lock{ m_mutex };
			m_cv.wait(lock, [this]() { return DataReady.load(); });	// or something that evaluates to true/false
			//m_cv.wait(lock, [&]() { return renderer.IsReady(); });	// or something that evaluates to true/false
			renderer.SwapBuffers();
			DataReady.store(false);
			lock.unlock();

			renderer.BeginFrame();
			renderer.EndFrame();		
		}

		renderer.Shutdown();
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