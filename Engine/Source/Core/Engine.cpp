#include "Pch.h"
#include "Engine.h"
#include "Application/Application.h"

#include "Logging/Logger.h"

#include "Resources/ResourceHolder.h"
#include "Rendering/Renderer/Renderer.h"
#include "Audio/AudioController.h"
#include "Input/InputHandler.h"
#include "Editor/Editor.h"
#include "Platform/Window/Window.h"
#include "Rendering/Shader/Shader.h"
#include "Rendering/Text/Renderer/TextRenderer.h"
#include "Physics/Physics.h"
#include "Utility/Utility.h"
#include "Time/Timer.h"
#include "Threading/ThreadPool.h"

#include "ECS/ECS.h"
#include "ECS/Systems/CoreSystems.h"
#include "ECS/Components/CoreComponents.h"
#include "EngineFacade.h"

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
	}

	void Engine::HandleEvent(TerminationEvent& event)
	{
		m_isRunning = false;
	}

	bool Engine::Init()
	{
		glfwSetErrorCallback(ErrorCallbackGLFW); // do in window class?

		Logger::Initialize("../Engine/Logs/engine_debug.log");

		RegisterModules();
		EventDispatcher::GetInstance().Subscribe(this);

		if (!m_moduleManager.Init())
		{
			Logger::LogInfo("Engine::Initialization - Successfully Completed!");
			return false;
		}

		// do in game?
		ResourceHolder<GLSLShader>::GetInstance().LoadResources("../Engine/Assets/Json/Resources/Shaders.json");

		//(LoadResources(); // Do in LoadModules?
		m_moduleManager.LoadModules();

		SetupECS();

		m_application.OnCreate(); 
		
		Logger::LogInfo("Engine::Initialization - Successfully Completed!");

		// SparseSet<TransformComponent, Entity> sparseSet;


		return (m_isRunning = true);
	}

	void Engine::Shutdown()
	{
		m_application.OnDestroy();
		m_moduleManager.Shutdown();

		EventDispatcher::GetInstance().Unsubscribe(this);
		Logger::Shutdown();
	}

	void Engine::Run()
	{
		auto ecs = m_moduleManager.GetModule<ECSCoordinator>().lock(); // Call lock here, or in the loop?
		auto& timer = m_moduleManager.GetModule<Utility>().lock()->GetTimer();
		auto window = m_moduleManager.GetModule<Window>().lock();

		while (m_isRunning)	// Todo, use enum for GameState instead? !GameState::EXIT or call function in Application? ShouldRun()?
		{
			PROFILE_FUNCTION("Engine::Run (Game Loop): ");

 			timer.Update();
			const float deltaTime = timer.GetDeltaTime();

			EventDispatcher::GetInstance().DispatchEvents();

			ecs->Update(deltaTime);
			m_application.OnUpdate(deltaTime);

//#ifdef DEBUG
			if (window)
				window->SetTitle("Fps: " + std::to_string((int)timer.GetAverageFPS())); // TODO; Get Draw calls... (have system do this)?
//#endif 
		}
	}

	void Engine::RegisterModules() // load from file instead?
	{
		m_moduleManager.RegisterModule<Window>(); // have return module pointer?

		auto window = m_moduleManager.GetModule<Window>().lock();

		m_moduleManager.RegisterModule<Renderer>(*window);
		m_moduleManager.RegisterModule<TextRenderer>();


		m_moduleManager.RegisterModule<InputHandler>();
		m_moduleManager.RegisterModule<AudioController>();
		m_moduleManager.RegisterModule<ECSCoordinator>(); // accept input handler and renderer?
		m_moduleManager.RegisterModule<Physics>();
		m_moduleManager.RegisterModule<Utility>();

#ifdef DEBUG
		m_moduleManager.RegisterModule<Editor>();
#endif

		EngineFacade::Register(m_moduleManager.GetModule<ECSCoordinator>());
	}

	void Engine::SetupECS()
	{
		auto ecs = m_moduleManager.GetModule<ECSCoordinator>().lock();

		auto window = m_moduleManager.GetModule<Window>().lock();
		auto editor = m_moduleManager.GetModule<Editor>();
		auto utility = m_moduleManager.GetModule<Utility>().lock();

		ecs->RegisterSystem<TimeSystem>("TimeSystem", utility->GetTimer());
		ecs->RegisterSystem<InputSystem>("InputSystem",   *m_moduleManager.GetModule<InputHandler>().lock(), *window);
		
		ecs->RegisterSystem<AudioSystem>("AudioSystem",   *m_moduleManager.GetModule<AudioController>().lock());
		ecs->RegisterSystem<RenderSystem>("RenderSystem", m_moduleManager.GetModule<Renderer>(), !editor.expired() ? editor : std::weak_ptr<Editor>(), IVector2{1400, 800});

#if DEBUG

		ecs->RegisterSystem<EditorSystem>("EditorSystem", *editor.lock());

#endif // DEBUG

		ecs->RegisterComponent<TransformComponent>("TransformComponent");
		ecs->RegisterComponent<VelocityComponent>("VelocityComponent");
		ecs->RegisterComponent<CameraComponent>("CameraComponent");
		ecs->RegisterComponent<SpriteComponent>("SpriteComponent");
		ecs->RegisterComponent<InputComponent>("InputComponent");
		ecs->RegisterComponent<AudioComponent>("AudioComponent");
		ecs->RegisterComponent<UIComponent>("UIComponent");
		ecs->RegisterComponent<TimerComponent>("TimerComponent");
		ecs->RegisterComponent<TagComponent>("TagComponent");

		ecs->RegisterComponent<TextComponent>("TextComponent");
		ecs->RegisterComponent<SceneTransitionComponent>("SceneTransitionComponent");
	}

	/*void Engine::LoadResources()
	{
	}*/
}