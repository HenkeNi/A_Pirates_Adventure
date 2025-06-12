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

// Put in register.h?
#include "ECS/Registry/ComponentRegistry.h"
#include "ECS/Registry/SystemRegistry.h"

// create a single Systems.h?
#include "ECS/Systems/RenderSystem.h"

#include "Rendering/Shader/Shader.h" // remove?

#include <GLFW/glfw3.h> // try remove!
#include "Rendering/Texture/Subtexture2D.h"
#include "ECS/Systems/UISystem.h"
#include "../../../Game/Source/Systems/SceneTransitionSystem.h"

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
		serviceFactory.Register<PrefabRegistry>("PrefabRegistry");
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
		prefabRegistry.LoadPrefabs("../Engine/Assets/Json/Prefabs/Prefab_UI.json"); // load from game or engine?

		// Elsewhere??
		// ECSRegistry::GetEntityFactory().Initialize(m_services.TryGetWeak<PrefabRegistry>());
	}

	void Engine::SetupECS()
	{
		// TODO; do static initalization instead?

		// Register components
		//auto& componentRegistry = m_services.Get<TypeRegistry<ComponentRegistryEntry, ComponentID>>();
		auto& componentRegistry = m_services.Get<ComponentRegistry>();
		
		// Transform Component
		RegisterComponent<TransformComponent>(componentRegistry, "TransformComponent",
			[](EntityHandle& handle, const Prefab::ComponentData& data)
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
			[](EntityHandle& handle, const Prefab::ComponentData& data)
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
			[](EntityHandle& handle, const Prefab::ComponentData& data)
			{
				auto& component = handle.GetComponent<CameraComponent>();

				// TODO...
			});

		// Sprite Component
		RegisterComponent<SpriteComponent>(componentRegistry, "SpriteComponent",
			[](EntityHandle& handle, const Prefab::ComponentData& data)
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
			[](EntityHandle& handle, const Prefab::ComponentData& data)
			{
				auto& component = handle.GetComponent<UIComponent>();

				// component->RenderDepth = std::get<int>(properties.at("render_depth"));
				// std::string texture = std::get<std::string>(properties.at("texture"));
				// IVector2 coordinates = std::get<IVector2>(properties.at("coordinates"));

				// component->Subtexture = ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().GetResource({ texture, coordinates.x, coordinates.y });
				// component->DefaultColor = component->CurrentColor = std::get<FVector4>(properties.at("color"));
				// component->RenderDepth = std::get<int>(properties.at("render_depth"));
			});
		
		// Input Component
		RegisterComponent<InputComponent>(componentRegistry, "InputComponent",
			[](EntityHandle& handle, const Prefab::ComponentData& data)
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
			[](EntityHandle& handle, const Prefab::ComponentData& data)
			{
				auto& component = handle.GetComponent<AudioComponent>();
			});
		
		// Tag Component
		RegisterComponent<TagComponent>(componentRegistry, "TagComponent",
			[](EntityHandle& handle, const Prefab::ComponentData& data)
			{
				auto& component = handle.GetComponent<TagComponent>();
			});
		
		// Timer Component
		RegisterComponent<TimerComponent>(componentRegistry, "TimerComponent",
			[](EntityHandle& handle, const Prefab::ComponentData& data)
			{
				auto& component = handle.GetComponent<TimerComponent>();

				//component->Duration = (float)std::get<double>(properties.at("duration"));
				//
				//		assert(properties.contains("callback") && "No callback registered");
				//
				//		std::string callbackKey = std::get<std::string>(properties.at("callback"));
				//		auto itr = CallbackRegistry::Callbacks.find(callbackKey.c_str());
				//
				//		if (itr != CallbackRegistry::Callbacks.end())
				//			component->Callback = itr->second;
			});
		
		// Text Component
		RegisterComponent<TextComponent>(componentRegistry, "TextComponent",
			[](EntityHandle& handle, const Prefab::ComponentData& data)
			{
				auto& component = handle.GetComponent<TextComponent>();
			});
		
		// Scene Transition Component
		RegisterComponent<SceneTransitionComponent>(componentRegistry, "SceneTransitionComponent",
			[](EntityHandle& handle, const Prefab::ComponentData& data)
			{
				auto& component = handle.GetComponent<SceneTransitionComponent>();
			});



		// Register systems
		auto& systemRegistry = m_services.Get<SystemRegistry>();

		RegisterSystem<CameraSystem>(systemRegistry, "CameraSystem");
		RegisterSystem<RenderSystem>(systemRegistry, "RenderSystem");
		RegisterSystem<UISystem>(systemRegistry, "UISystem");
		RegisterSystem<TimeSystem>(systemRegistry, "TimeSystem");
		RegisterSystem<SceneTransitionSystem>(systemRegistry, "SceneTransitionSystem");

		//systemRegistry.Register<RenderSystem>("RenderSystem");
		//systemRegistry.Register<AudioSystem>("AudioSystem");

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
}