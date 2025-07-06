#include "Pch.h"
#include "Engine.h"
#include "Application/Application.h"
#include "Services/Scene/Scene.h"
#include "Services/Services.h"
#include "Services/ServiceGraph.h"
#include "Resource/ResourceAliases.h"
#include "Resource/ResourceLoader.h"
#include "EngineSetup.h"
#include "Logging/Logger.h"

namespace Hi_Engine
{
	Engine::Engine(Application& app)
		: m_application{ app }, m_isRunning{ false }
	{
	}

	bool Engine::Init()
	{
		Logger::Initialize("../Engine/Logs/engine_debug.log"); // make into service?

		RegisterServices();
		
		auto& configService = m_serviceRegistry.Get<ConfigService>();

		auto result = configService.LoadFromFile("../Engine/Assets/Json/Config/engine_config.json");
		if (result != ConfigService::eLoadResult::Success)
		{
			Logger::LogInfo("Engine::Initialization - Failed to load Engine config!");
			return false;
		}

		auto& windowService = m_serviceRegistry.Get<WindowService>();
		
		if (!windowService.Initialize(configService.GetWindowConfig()))
		{
			Logger::LogInfo("Engine::Initialization - Failed to initialize window service!");
			return false;
		}

		auto& renderService = m_serviceRegistry.Get<RenderService>();

		if (!renderService.Initialize())
		{
			Logger::LogInfo("Engine::Initialization - Failed to initialize render service!");
			return false;
		}

		auto& audioService = m_serviceRegistry.Get<AudioService>();
		
		if (!audioService.Initialize())
		{
			Logger::LogInfo("Engine::Initialization - Failed to initialize audio service!");
			return false;
		}

		auto& physicsService = m_serviceRegistry.Get<PhysicsService>();

		if (!physicsService.Initialize())
		{
			Logger::LogInfo("Engine::Initialization - Failed to initialize physics service!");
			return false;
		}

		auto& inputServivce = m_serviceRegistry.Get<InputService>();
		inputServivce.AttachToWindow(windowService.GetHandle());

		EngineSetup::RegisterSystems(m_serviceRegistry.Get<SystemRegistryService>());
		EngineSetup::RegisterComponents(m_serviceRegistry.Get<ComponentRegistryService>());
		EngineSetup::RegisterEvents(m_serviceRegistry.Get<EventRegistryService>());

		LoadResources();
		ConfigureRenderer();

		m_application.Initialize(&m_serviceRegistry);
		m_application.OnCreate(); 
		
		Logger::LogInfo("Engine::Initialization - Successfully Completed!");

		return (m_isRunning = true);
	}

	void Engine::Shutdown()
	{
		m_application.OnDestroy();

		m_serviceRegistry.ForEach([](auto& service) { service->Shutdown(); });

		// EventDispatcher::GetInstance().Unsubscribe(this);

		Logger::Shutdown();
	}

	void Engine::Run()
	{
		while (m_isRunning)	// Todo, use enum for GameState instead? !GameState::EXIT or call function in Application? ShouldRun()?
		{
			PROFILE_FUNCTION("Engine::Run (Game Loop): ");

			auto& timer = m_serviceRegistry.Get<TimeService>();
			timer.Update();
			
			const float deltaTime = timer.GetDeltaTime();

			if (auto eventService = m_serviceRegistry.TryGetWeak<EventService>().lock())
			{
				eventService->DispatchEvents();
			}

			auto& sceneManager = m_serviceRegistry.Get<SceneService>();
			
			auto activeScene = sceneManager.GetActive();
			if (auto scene = activeScene.lock())
			{
				scene->Update(deltaTime);
			}

			m_application.OnUpdate(deltaTime);

#ifdef DEBUG
			m_serviceRegistry.Get<WindowService>().SetTitle("Fps: " + std::to_string((int)timer.GetAverageFPS())); // TODO; Get Draw calls... (have system do this)?
#endif 
		}
	}

	void Engine::RegisterServices()
	{
		ServiceGraph graph;
		graph.Register<AudioService>();
		graph.Register<ConfigService>();
		graph.Register<EventService>();
		graph.Register<InputService, EventService>();
		graph.Register<PhysicsService>();
		graph.Register<RenderService, WindowService>();
		graph.Register<TextureAssetService>();
		graph.Register<SubtextureAssetService>();
		graph.Register<AudioAssetService>();
		graph.Register<ShaderAssetService>();
		graph.Register<SceneService>();
		graph.Register<TaskService>();
		graph.Register<TimeService>();
		graph.Register<WindowService, EventService>();
		graph.Register<EventRegistryService>();
		graph.Register<ComponentRegistryService>();
		graph.Register<SystemRegistryService>();
		graph.Register<SceneRegistryService>();
		graph.Register<PrefabRegistryService>();

		for (auto& [type, service] : graph.Build())
		{
			m_serviceRegistry.Insert(service, type);
		}
	}

	void Engine::ConfigureRenderer()
	{
		auto& shaderAssetService = m_serviceRegistry.Get<ShaderAssetService>();
		auto shader = shaderAssetService.GetResource("sprite_batch");
		m_serviceRegistry.Get<RenderService>().SetShader(shader.get());
	}

	void Engine::LoadResources()
	{
		auto& prefabRegistry = m_serviceRegistry.Get<PrefabRegistryService>();

		prefabRegistry.LoadPrefabs("../Engine/Assets/Json/Prefabs/ui_prefab.json");
		prefabRegistry.LoadPrefabs("../Engine/Assets/Json/Prefabs/camera_prefab.json");
		prefabRegistry.LoadPrefabs("../Engine/Assets/Json/Prefabs/utility_prefab.json");

		LoadTexturesFromJson(m_serviceRegistry, "../Game/Assets/Json/Resources/Textures2.json");
		LoadShadersFromJson(m_serviceRegistry.Get<ShaderAssetService>(), "../Engine/Assets/Json/Resources/Shaders.json");
		LoadAudioFromJson(m_serviceRegistry.Get<AudioAssetService>(), "../Game/Assets/Json/Audio/Audio.json");
	}

	void Engine::OnEvent(TerminationEvent& event)
	{
		m_isRunning = false;
	}
}