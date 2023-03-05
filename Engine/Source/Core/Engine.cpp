#include "Pch.h"
#include "Engine.h"
#include "Application.h"
#include "Resources/ResourceHolder.hpp"

#include "Rendering/Renderers/SpriteRenderer/SpriteRenderer.h"

//#include "Resources/ResourceHolder.hpp"
//#include "Rendering/Shader/Shader.h"
//#include "Rendering/Texture/Texture.h"


extern Hi_Engine::Application* Hi_Engine::CreateApplication();

namespace Hi_Engine
{
	Engine::Engine()
		: m_application{ Hi_Engine::CreateApplication() }, m_isRunning{true}
	{
	}

	bool Engine::Init()
	{
		if (!SetupWindow() || glewInit() != GLEW_OK) // do glewInit() in Graphics??
			return false;

		ResourceHolder<Texture2D>::GetInstance().FetchAll("../Bin/Assets/Json/Resources/Textures.json");
		ResourceHolder<Shader>::GetInstance().FetchAll("../Bin//Assets/Json/Resources/Shaders.json");

		auto& SpriteRenderer = SpriteRenderer::GetInstance();
		SpriteRenderer.Init();
		SpriteRenderer.SetShader(&ResourceHolder<Shader>::GetInstance().GetResource("Sprite"));
		// TextureHolder -> usei nstead...
		SpriteRenderer.ConfigureShader(800, 600); // Or call from SetShader??


		// TODO;

		// Init renderers??
		// Configure all shaders... => for each function??




		// Do in Graphics.h??? -> 'SetupOpenGL()'?
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);





		if (m_application)
			m_application->OnCreate();


		return true;
	}

	bool Engine::IsRunning() const
	{
		return m_window.IsOpen() && m_isRunning;
	}

	void Engine::ProcessInput()
	{
		m_window.PollEvents();					// Todo; do here, or at the end of the frame?
		m_inputHandler.ProcessInput();
	}

	void Engine::Update()
	{
		m_timer.Update(); // HERE Or at the end of the loop??

		float deltaTime = m_timer.GetDeltaTime();

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

		// FIX...?? have game objects add draw calls, in here draw them all at the same time...
		m_application->OnDraw();
		
		m_window.SwapBuffers();
	}

	void Engine::Shutdown()
	{
		if (m_window.IsOpen())
			m_window.Close();

		if (m_application)
		{
			m_application->OnDestroy();
			delete m_application;
		}

	}

	bool Engine::SetupWindow()
	{
		// TODO; load elsewhere??? Window loader
		std::ifstream ifs{ "../Bin/Assets/Json/Window/Window.json" };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		if (!document.Parse(content.c_str()).HasParseError())
		{
			auto obj = document["window"].GetObj();

			WindowData data;
			data.m_name = obj["name"].GetString();
			data.m_size = { obj["size"]["width"].GetUint(), obj["size"]["height"].GetUint() };
			data.m_iconPath = obj["icon_path"].GetString();

			return m_window.Init(data);
		}
		return false;
	}

	// TODO; use keycodes mapped to Action events instead??
	void Engine::MapControlls() 
	{
		m_inputHandler.MapEvent(); // Pass in key 
	}
}