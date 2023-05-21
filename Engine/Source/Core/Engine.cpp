#include "Pch.h"
#include "Engine.h"
#include "Application.h"
#include "Resources/ResourceHolder.hpp"

#include "Rendering/Renderers/SpriteRenderer/SpriteRenderer.h"
#include "Rendering/Renderers/BillboardRenderer/BillboardRenderer.h"

#include "Messaging/Dispatcher/Dispatcher.h"

#include "FileIO/FileSystem.h"
#include "FileIO/Parsers/WindowParser.h"


extern Hi_Engine::Application* Hi_Engine::CreateApplication();

namespace Hi_Engine
{
	Engine::Engine()
		: m_application{ CreateApplication() }, m_isRunning{ true }
	{
	}

	bool Engine::Init()
	{
		if (!SetupWindow() || glewInit() != GLEW_OK || !m_application) // do glewInit() in Graphics??
			return false;

		stbi_set_flip_vertically_on_load(true);

		ResourceHolder<Texture2D>::GetInstance().FetchAll("../Bin/Assets/Json/Resources/Textures.json");
		ResourceHolder<Shader>::GetInstance().FetchAll("../Bin//Assets/Json/Resources/Shaders.json");
        		 
		//SetupRendering();
		//SpriteRenderer::GetInstance().Init();
		BillboardRenderer::GetInstance().Init();


		//SpriteRenderer::GetInstance().SetCamera(&m_camera); // TEST!



	
		/*glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);*/

		// glEnable(GL_DEPTH_TEST);   ????

		m_application->OnCreate(); 

		return true;
	}

	bool Engine::IsRunning() const
	{
		return m_window.IsOpen() && m_isRunning;
	}

	void Engine::ProcessInput()
	{
		// Do at the end of frame??
		Dispatcher::GetInstance().DispatchEvents();


		m_window.PollEvents();					// Todo; do here, or at the end of the frame?
		m_inputHandler.ProcessInput();
	}

	void Engine::Update()
	{
		m_timer.Update(); // HERE Or at the end of the loop??

		const float deltaTime = m_timer.GetDeltaTime();

		if (m_application)
			m_application->OnUpdate(deltaTime);
	}

	void Engine::LateUpdate()
	{
		// Update AI(?)
		// Check collisions
	}

	void Engine::Draw()
	{
		m_window.ClearScreen();

		//SpriteRenderer::GetInstance().BeginRendering();



		//SpriteRenderer::GetInstance().EndRendering();




		// Set view projection/transform somewhere

		//SpriteRenderer::GetInstance().BeginBatch(); // TEST


		// abstraction layer?? so instead of SPriteRenderer::Render its Renderer::Render (and renderer contains active renderer(sprite/text, etc:.)??


		// FIX...?? have game objects add draw calls, in here draw them all at the same time...
		m_application->OnDraw();

		//SpriteRenderer::GetInstance().EndBatch(); // TEST
		//SpriteRenderer::GetInstance().Flush(); // TEST

		m_window.SwapBuffers();
	}

	void Engine::Shutdown()
	{
		if (m_window.IsOpen())
			m_window.Close();

		SpriteRenderer::GetInstance().Shutdown();

		if (m_application)
		{
			m_application->OnDestroy();
			delete m_application;
		}

	}

	bool Engine::SetupWindow()
	{
		auto windowData = FileSystem::ParseJson<WindowParser, WindowData>("../Bin/Assets/Json/Window/Window.json");

		return m_window.Init(windowData);
	}

	void Engine::SetupRendering()
	{
		auto& SpriteRenderer = SpriteRenderer::GetInstance();
		SpriteRenderer.Init();
		SpriteRenderer.SetShader(&ResourceHolder<Shader>::GetInstance().GetResource("Core"));
	}
}