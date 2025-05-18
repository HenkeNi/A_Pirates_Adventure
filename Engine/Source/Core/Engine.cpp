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
#include "Rendering/Text/Renderer/TextRenderer.h"

#include "Time/Timer.h"
#include "Threading/ThreadPool.h"

#include "Physics/Physics.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Service/ServiceFactory.h"

#include "ECS/Components/CoreComponents.h" // remoev?
#include "ECS/Systems/CoreSystems.h"

#include "Rendering/Shader/Shader.h" // remove?

#include <GLFW/glfw3.h> // try remove!

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

		RegisterServiceTypes();

		auto result = m_engineConfig.LoadFromFile("../Engine/Assets/Json/Config/engine_config.json");
		if (result != EngineConfig::eLoadResult::Success)
		{
			Logger::LogInfo("Engine::Initialization - Failed to load Engine config!");
			return false;
		}

		if (!SetupServices())
			return false;

		EventDispatcher::GetInstance().Subscribe(this);

		// Make service instead?
		ResourceHolder<GLSLShader>::GetInstance().LoadResources("../Engine/Assets/Json/Resources/Shaders.json");

		SetupECS();

		m_application.Initialize(&m_services);
		m_application.OnCreate(); 
		
		Logger::LogInfo("Engine::Initialization - Successfully Completed!");

		return (m_isRunning = true);
	}

	void Engine::Shutdown()
	{
		m_application.OnDestroy();

		m_services.ForEach([](auto& service) { service->Shutdown(); });

		EventDispatcher::GetInstance().Unsubscribe(this);
		Logger::Shutdown();
	}

	void Engine::Run()
	{
		while (m_isRunning)	// Todo, use enum for GameState instead? !GameState::EXIT or call function in Application? ShouldRun()?
		{
			PROFILE_FUNCTION("Engine::Run (Game Loop): ");

			auto& timer = m_services.Get<Timer>();
			timer.Update();
			
			const float deltaTime = timer.GetDeltaTime();

			EventDispatcher::GetInstance().DispatchEvents();

			auto& sceneManager = m_services.Get<SceneManager>();
			
			auto activeScene = sceneManager.GetActive();
			if (auto scene = activeScene.lock())
			{
				scene->Update(deltaTime);
			}

			m_application.OnUpdate(deltaTime);

#ifdef DEBUG
			m_services.Get<Window>().SetTitle("Fps: " + std::to_string((int)timer.GetAverageFPS())); // TODO; Get Draw calls... (have system do this)?
#endif 

			// TEMP
			std::cout << "\n\n";
		}
	}

	void Engine::RegisterServiceTypes()
	{
		auto& serviceFactory = ServiceFactory::GetInstance();
		
		serviceFactory.Register<Renderer>("OpenGLRenderer");
		serviceFactory.Register<InputHandler>("GLFWInput");
		serviceFactory.Register<Window>("GLFWWindow");
		serviceFactory.Register<AudioController>("IrrKlangAudio");
		serviceFactory.Register<Physics>("Box2DPhysics");

		serviceFactory.Register<SceneManager>("SceneManager");
		serviceFactory.Register<TextRenderer>("TextRenderer");
		serviceFactory.Register<ThreadPool>("ThreadPool");
		serviceFactory.Register<Timer>("Timer");
		serviceFactory.Register<Editor>("Editor");
	}

	bool Engine::SetupServices()
	{
		auto& factory = ServiceFactory::GetInstance();

		const auto& windowConfig = m_engineConfig.GetWindowConfig();
		auto window = factory.Create<Window>(windowConfig.Type.c_str());
		if (!window)
		{
			Logger::LogError("Failed to create Window service: " + windowConfig.Type);
			return false;
		}

		window->Initialize(windowConfig);
		m_services.Insert(window);

		const auto& inputConfig = m_engineConfig.GetInputConfig();
		auto input = factory.Create<InputHandler>(inputConfig.Type.c_str());
		m_services.Insert(input);

		const auto& rendererConfig = m_engineConfig.GetRendererConfig();
		auto renderer = factory.Create<Renderer>(rendererConfig.Type.c_str());
		renderer->Initialize();
		m_services.Insert(renderer);

		const auto& audioConfig = m_engineConfig.GetAudioConfig();
		auto audio = factory.Create<AudioController>(audioConfig.Type.c_str());
		audio->Initialize();
		m_services.Insert(audio);

		const auto& physicsConfig = m_engineConfig.GetPhysicsConfig();
		auto physics = factory.Create<Physics>(physicsConfig.Type.c_str());
		physics->Initialize();
		m_services.Insert(physics);

		m_services.Emplace<SceneManager>();
		// m_services.Emplace<TextRenderer>();
		m_services.Emplace<ThreadPool>();
		m_services.Emplace<Timer>();
		//m_services.Emplace<Editor>();
	}

	void Engine::SetupECS()
	{
//		auto ecs = m_moduleManager.GetModule<World>().lock();
//
//		auto window = m_moduleManager.GetModule<Window>().lock();
//		auto editor = m_moduleManager.GetModule<Editor>();
//		auto utility = m_moduleManager.GetModule<Utility>().lock();
//
//		ecs->RegisterSystem<TimeSystem>("TimeSystem", utility->GetTimer());
//		ecs->RegisterSystem<InputSystem>("InputSystem",   *m_moduleManager.GetModule<InputHandler>().lock(), *window);
//		
//		ecs->RegisterSystem<AudioSystem>("AudioSystem",   *m_moduleManager.GetModule<AudioController>().lock());
//		ecs->RegisterSystem<RenderSystem>("RenderSystem", m_moduleManager.GetModule<Renderer>(), !editor.expired() ? editor : std::weak_ptr<Editor>(), IVector2{1400, 800});
//
//#if DEBUG
//
//		ecs->RegisterSystem<EditorSystem>("EditorSystem", *editor.lock());
//
//#endif // DEBUG
//
//		ecs->RegisterComponent<TransformComponent>("TransformComponent");
//		ecs->RegisterComponent<VelocityComponent>("VelocityComponent");
//		ecs->RegisterComponent<CameraComponent>("CameraComponent");
//		ecs->RegisterComponent<SpriteComponent>("SpriteComponent");
//		ecs->RegisterComponent<InputComponent>("InputComponent");
//		ecs->RegisterComponent<AudioComponent>("AudioComponent");
//		ecs->RegisterComponent<UIComponent>("UIComponent");
//		ecs->RegisterComponent<TimerComponent>("TimerComponent");
//		ecs->RegisterComponent<TagComponent>("TagComponent");
//
//		ecs->RegisterComponent<TextComponent>("TextComponent");
//		ecs->RegisterComponent<SceneTransitionComponent>("SceneTransitionComponent");
	}

	/*void Engine::LoadResources()
	{
	}*/
}