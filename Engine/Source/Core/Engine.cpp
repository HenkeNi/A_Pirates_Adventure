#include "Pch.h"
#include "Engine.h"
#include "Application.h"
#include "FileIO/FileSystem.h"
#include "FileIO/Parsers/WindowParser.h"
#include "Resources/ResourceHolder.hpp"
#include "Rendering/Renderers/SpriteRenderer/SpriteRenderer.h"
#include "Rendering/Renderers/BillboardRenderer/BillboardRenderer.h"
#include "Rendering/Renderers/PrimitiveRenderer/PrimitiveRenderer.h"
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

		SetupRendering();

		m_application->OnCreate(); 

		return (m_isRunning = true);
	}

	void Engine::GameLoop()
	{
		assert(m_application && "Failed to launch application");
		Timer timer;

		while (IsRunning())
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
			m_window.SwapBuffers();
		}
	}

	void Engine::Shutdown()
	{
		if (m_window.IsOpen())
			m_window.Close();

		BillboardRenderer::GetInstance().Shutdown();
		SpriteRenderer::GetInstance().Shutdown();

		if (m_application)
		{
			m_application->OnDestroy();
			delete m_application;
		}
	}
		
	bool Engine::IsRunning() const
	{
		return m_window.IsOpen() && m_isRunning;
	}

	bool Engine::CreateWindow()
	{
		auto windowData = FileSystem::ParseJson<WindowParser, WindowData>("../Engine/Assets/Json/Window/Window.json");
		return m_window.Init(windowData);
	}

	void Engine::SetupRendering()
	{
		stbi_set_flip_vertically_on_load(true);

		glEnable(GL_DEPTH_TEST);		
		// glEnable(GL_BLEND) ?? does what?
		// glEnable(GL_CULL_FACE);		// Disable back faces?? only for 3D?!
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);*/
		// glFrontFace(GL_CCW);		// Counter clockwise

		BillboardRenderer::GetInstance().Init();
		SpriteRenderer::GetInstance().Init();
		PrimitiveRenderer::GetInstance().Init();
	}
}