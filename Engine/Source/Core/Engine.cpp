#include "Pch.h"
#include "Engine.h"
#include "Application.h"

extern Hi_Engine::Application* Hi_Engine::CreateApplication();

namespace Hi_Engine
{
	Engine::Engine()
		: m_application{ nullptr }, m_isRunning{ true }
	{

	}

	bool Engine::Init()
	{
		m_application = Hi_Engine::CreateApplication();

		WindowData wData; // FileSystem.LoadWindowData()???
		wData.m_size = { 800, 600 };
		wData.m_name = "A Pirate's Adventure!";
		wData.m_iconPath = "....";

		if (!m_window.Init(wData))
			return false;


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

	}

	void Engine::Shutdown()
	{
		if (m_window.IsOpen())
			m_window.Close();

		if (m_application)
			m_application->OnDestroy();
	}
}