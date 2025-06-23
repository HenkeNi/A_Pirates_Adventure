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
#include "Prefab/PrefabRegistry.h"

#include "Time/Timer.h"
#include "Threading/ThreadPool.h"

#include "Physics/Physics.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Service/ServiceFactory.h"

#include "ECS/Components/CoreComponents.h" // remoev?
#include "ECS/Systems/CoreSystems.h"
#include "ECS/Utility/EntityHandle.h"
#include "ECS/Factory/EntityFactory.h"


#include "Registry/RegistryTraits.h"
#include "Registry/RegistryHelpers.h"

// create a single Systems.h?
#include "ECS/Systems/RenderSystem.h"

#include "Rendering/Shader/Shader.h" // remove?

#include <GLFW/glfw3.h> // try remove!
#include "Rendering/Texture/Subtexture2D.h"
#include "ECS/Systems/UISystem.h"
#include "../../../Game/Source/Systems/SceneTransitionSystem.h"
#include "Event/Core/EventBus.h"

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

	void Engine::OnEvent(TerminationEvent& event)
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

		//EventBus::GetInstance().Subscribe(this);

		RegisterSystems();
		RegisterComponents();

		m_application.Initialize(&m_services);
		m_application.OnCreate(); 
		
		Logger::LogInfo("Engine::Initialization - Successfully Completed!");

		return (m_isRunning = true);
	}

	void Engine::Shutdown()
	{
		m_application.OnDestroy();

		m_services.ForEach([](auto& service) { service->Shutdown(); });

		// EventDispatcher::GetInstance().Unsubscribe(this);
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

			if (auto eventBus = m_services.TryGetWeak<EventBus>().lock())
			{
				eventBus->DispatchEvents();
				//EventDispatcher::GetInstance().DispatchEvents();
			}

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
		serviceFactory.Register<PrefabRegistry>("PrefabRegistry");
	}

	void Engine::RegisterComponents()
	{
		// TODO; do static initalization instead?

		auto& componentRegistry = m_services.Get<ComponentRegistry>();

		// Transform Component
		RegisterComponent<TransformComponent>(componentRegistry, "TransformComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<TransformComponent>();

				auto position = GetPropertyValueOrDefault(data, "position", std::vector<PropertyValue>{ 0.f, 0.f });
				component.Position.x = std::get<float>(position[0]);
				component.Position.y = std::get<float>(position[1]);

				auto scale = GetPropertyValueOrDefault(data, "scale", std::vector<PropertyValue>{ 0.f, 0.f });
				component.Scale.x = std::get<float>(scale[0]);
				component.Scale.y = std::get<float>(scale[1]);


				auto pivot = GetPropertyValueOrDefault(data, "pivot", std::vector<PropertyValue>{ 0.f, 0.f });
				component.Pivot.x = std::get<float>(pivot[0]);
				component.Pivot.y = std::get<float>(pivot[1]);

				float rotation = GetPropertyValueOrDefault(data, "rotation", float{ 0.f });
				component.Rotation = rotation;
			});

		// Velocity Component
		RegisterComponent<VelocityComponent>(componentRegistry, "VelocityComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<VelocityComponent>();

				auto velocity = GetPropertyValueOrDefault(data, "velocity", std::vector<PropertyValue>{ 0.f, 0.f });
				component.Velocity.x = std::get<float>(velocity[0]);
				component.Velocity.y = std::get<float>(velocity[1]);

				float baseSpeed = GetPropertyValueOrDefault(data, "base_speed", float{ 0.f });
				component.BaseSpeed = baseSpeed;

				// TODO... add other fields
			});

		// Camera Component
		RegisterComponent<CameraComponent>(componentRegistry, "CameraComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<CameraComponent>();

				// TODO...
			});

		// Sprite Component
		RegisterComponent<SpriteComponent>(componentRegistry, "SpriteComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<SpriteComponent>();

				// temp...
				std::string texture = GetPropertyValueOrDefault<std::string>(data, "texture", "");

				auto coordinates = GetPropertyValueOrDefault(data, "coordinates", std::vector<PropertyValue>{ 0.f, 0.f });
				int xCoord = std::get<int>(coordinates[0]);
				int yCoord = std::get<int>(coordinates[1]);

				//component.Subtexture = ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().GetResource({ texture, xCoord, yCoord });
				//component->DefaultColor = component->CurrentColor = std::get<FVector4>(properties.at("color"));
				//component->RenderDepth = std::get<int>(properties.at("render_depth"));
			});

		// UI Component
		RegisterComponent<UIComponent>(componentRegistry, "UIComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<UIComponent>();

				std::string texture = GetPropertyValueOrDefault<std::string>(data, "texture", ""); // TODO; use some "error" texture as default...
				auto coordinates = GetPropertyValueOrDefault(data, "coordinates", std::vector<PropertyValue>{ 0, 0 });

				// temp... (title text has no texture)...
				if (texture != "")
					component.Subtexture = ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().GetResource({ texture, std::get<int>(coordinates[0]), std::get<int>(coordinates[1]) });
				component.RenderDepth = GetPropertyValueOrDefault<int>(data, "render_depth", 0);
				
				auto propertyColor = GetPropertyValueOrDefault(data, "color", std::vector<PropertyValue>{ 1.f, 1.f, 1.f, 1.f });

				FVector4 color;
				color.x = std::get<float>(propertyColor[0]);
				color.y = std::get<float>(propertyColor[1]);
				color.z = std::get<float>(propertyColor[2]);
				color.w = std::get<float>(propertyColor[3]);

				component.DefaultColor = component.DefaultColor = color;
			});

		// Input Component
		RegisterComponent<InputComponent>(componentRegistry, "InputComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<InputComponent>();

				// temp...
				component.InputStates.insert({ Hi_Engine::eKey::Key_W, false });
				component.InputStates.insert({ Hi_Engine::eKey::Key_A, false });
				component.InputStates.insert({ Hi_Engine::eKey::Key_S, false });
				component.InputStates.insert({ Hi_Engine::eKey::Key_D, false });
			});

		// Audio Component
		RegisterComponent<AudioComponent>(componentRegistry, "AudioComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<AudioComponent>();
			});

		// Tag Component
		RegisterComponent<TagComponent>(componentRegistry, "TagComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<TagComponent>();
			});

		// Timer Component
		RegisterComponent<TimerComponent>(componentRegistry, "TimerComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<TimerComponent>();

				component.Duration = GetPropertyValueOrDefault(data, "duration", 0.f);
				auto action = GetPropertyValueOrDefault(data, "action", std::unordered_map<std::string, PropertyValue>{});
				
				if (auto it = action.find("event"); it != action.end())
				{
					std::string eventName = std::get<std::string>(it->second);
					component.OnCompleted.EventName = std::move(eventName);
				}

				if (auto it = action.find("params"); it != action.end())
				{
					auto params = std::get<std::unordered_map<std::string, PropertyValue>>(it->second);

					for (const auto& [key, value] : params)
					{
						component.OnCompleted.Params.insert({ key, value });
					}
				}
			});

		// Text Component
		RegisterComponent<TextComponent>(componentRegistry, "TextComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<TextComponent>();
			});

		
	}

	void Engine::RegisterSystems()
	{
		// Register systems
		auto& systemRegistry = m_services.Get<SystemRegistry>();

		RegisterSystem<CameraSystem>(systemRegistry, "CameraSystem");

		RegisterSystem<RenderSystem>(systemRegistry, "RenderSystem",
			[](World& world, ServiceRegistry& registry)
			{
				const auto& size = registry.Get<Window>().GetSize();

				return std::make_unique<RenderSystem>(world, registry.TryGetWeak<Renderer>(), registry.TryGetWeak<Editor>(), size);
			});

		RegisterSystem<UISystem>(systemRegistry, "UISystem");

		RegisterSystem<TimeSystem>(systemRegistry, "TimeSystem",
			[](World& world, ServiceRegistry& registry)
			{
				return std::make_unique<TimeSystem>(world, registry.Get<Timer>());
			});

		RegisterSystem<SceneTransitionSystem>(systemRegistry, "SceneTransitionSystem",
			[](World& world, ServiceRegistry& registry)
			{
				return std::make_unique<SceneTransitionSystem>(world, registry.Get<SceneManager>());
			});

		RegisterSystem<AudioSystem>(systemRegistry, "AudioSystem",
			[](World& world, ServiceRegistry& registry)
			{
				return std::make_unique<AudioSystem>(world, registry.Get<AudioController>());
			});

		RegisterSystem<InputSystem>(systemRegistry, "InputSystem",
			[](World& world, ServiceRegistry& registry)
			{
				return std::make_unique<InputSystem>(world, registry.Get<InputHandler>(), registry.Get<Window>());
			});

		if constexpr (Utils::IsDebugBuild())
		{
			RegisterSystem<EditorSystem>(systemRegistry, "EditorSystem",
				[](World& world, ServiceRegistry& registry)
				{
					return std::make_unique<EditorSystem>(world, registry.Get<Editor>());
				});
		}
	}

	bool Engine::SetupServices()
	{
		auto& factory = ServiceFactory::GetInstance();

		m_services.Emplace<EventBus>(); // have emplace return instance???

		// TODO; use factory to create all services?? read from json?

		const auto& windowConfig = m_engineConfig.GetWindowConfig();
		auto window = factory.Create<Window>(windowConfig.Type.c_str()); // NEED TO PASS IN EVENT BUS?
		if (!window)
		{
			Logger::LogError("Failed to create Window service: " + windowConfig.Type);
			return false;
		}

		window->Initialize(windowConfig, m_services.TryGetWeak<EventBus>());
		m_services.Insert(window);

		const auto& inputConfig = m_engineConfig.GetInputConfig();
		auto input = factory.Create<InputHandler>(inputConfig.Type.c_str());
		input->AttachToWindow(window->GetHandle()); // is window (shared ptr) still valid?
		input->Init(m_services.TryGetWeak<EventBus>());
		m_services.Insert(input);

		const auto& rendererConfig = m_engineConfig.GetRendererConfig();
		auto renderer = factory.Create<Renderer>(rendererConfig.Type.c_str());
		renderer->Initialize(m_services.TryGet<Window>());
		// Make service instead?
		ResourceHolder<GLSLShader>::GetInstance().LoadResources("../Engine/Assets/Json/Resources/Shaders.json");
		renderer->SetShader(ResourceHolder<GLSLShader>::GetInstance().GetResource("sprite_batch").get());
		m_services.Insert(renderer);

		const auto& audioConfig = m_engineConfig.GetAudioConfig();
		auto audio = factory.Create<AudioController>(audioConfig.Type.c_str());
		audio->Initialize();
		m_services.Insert(audio);

		const auto& physicsConfig = m_engineConfig.GetPhysicsConfig();
		auto physics = factory.Create<Physics>(physicsConfig.Type.c_str());
		physics->Initialize();
		m_services.Insert(physics);

		m_services.Emplace<SceneRegistry>();
		m_services.Emplace<SceneManager>();
		// m_services.Emplace<TextRenderer>();
		m_services.Emplace<ThreadPool>();
		m_services.Emplace<Timer>();
		//m_services.Emplace<Editor>();
		m_services.Emplace<PrefabRegistry>();
		m_services.Emplace<TypeRegistry<ComponentRegistryEntry, ComponentID>>();
		m_services.Emplace<TypeRegistry<SystemRegistryEntry, SystemID>>();


		// Do else where??
		auto& prefabRegistry = m_services.Get<PrefabRegistry>();

		prefabRegistry.LoadPrefabs("../Engine/Assets/Json/Prefabs/ui_prefab.json"); // load from game or engine?
		prefabRegistry.LoadPrefabs("../Engine/Assets/Json/Prefabs/camera_prefab.json");
		prefabRegistry.LoadPrefabs("../Engine/Assets/Json/Prefabs/utility_prefab.json");
		//prefabRegistry.LoadPrefabs("../Engine/Assets/Json/Prefabs/world_time.json");

		// Elsewhere??
		// ECSRegistry::GetEntityFactory().Initialize(m_services.TryGetWeak<PrefabRegistry>());
	}
}