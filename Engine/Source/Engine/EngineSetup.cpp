#include "Pch.h"
#include "Engine.h"
#include "Services/Services.h"
#include "Services/ServiceRegistry.h"
#include "Services/Resource/ResourceAliases.h"
#include "Core/Registry/RegistryAliases.h"
#include "Core/Registry/RegistryHelpers.h"
#include "ECS/Systems/CoreSystems.h"
#include "ECS/Components/CoreComponents.h"
#include "Resource/ResourceLoader.h"
#include "Scene/SceneService.h" // Service/ not needed??
#include "EngineSetup.h"

namespace Hi_Engine::EngineSetup
{
	void RegisterSystems(SystemRegistryService& registry)
	{
		RegisterSystem<CameraSystem>(registry, "CameraSystem");

		RegisterSystem<RenderSystem>(registry, "RenderSystem",
			[](World& world, ServiceRegistry& registry)
			{
				const auto& size = registry.Get<WindowService>().GetSize();

				return std::make_unique<RenderSystem>(world, registry);
			});

		RegisterSystem<AudioSystem>(registry, "AudioSystem",
			[](World& world, ServiceRegistry& registry)
			{
				return std::make_unique<AudioSystem>(world, registry.TryGetWeak<AudioService>());
			});

		RegisterSystem<TimeSystem>(registry, "TimeSystem",
			[](World& world, ServiceRegistry& registry)
			{
				return std::make_unique<TimeSystem>(world, registry);
			});

		RegisterSystem<UISystem>(registry, "UISystem");

		RegisterSystem<InputSystem>(registry, "InputSystem",
			[](World& world, ServiceRegistry& registry)
			{
				return std::make_unique<InputSystem>(world, registry.Get<InputService>(), registry.Get<WindowService>());
			});
	}

	void RegisterComponents(ComponentRegistryService& registry)
	{

		// Camera Component
		RegisterComponent<CameraComponent>(registry, "CameraComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<CameraComponent>();

				// TODO...
			});

		// Sprite Component
		RegisterComponent<SpriteComponent>(registry, "SpriteComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<SpriteComponent>();

				// temp...
				std::string texture = GetPropertyValueOrDefault<std::string>(data, "texture", "");
				component.TextureData.TextureID = texture;

				auto coordinates = GetPropertyValueOrDefault(data, "coordinates", std::vector<PropertyValue>{ 0.f, 0.f });
				component.TextureData.Coordinates.x = std::get<int>(coordinates[0]);
				component.TextureData.Coordinates.y = std::get<int>(coordinates[1]);

				//component.Subtexture = ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().GetResource({ texture, xCoord, yCoord });
				//component->DefaultColor = component->CurrentColor = std::get<FVector4>(properties.at("color"));
				//component->RenderDepth = std::get<int>(properties.at("render_depth"));
			});



		// Text Component
		RegisterComponent<TextComponent>(registry, "TextComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<TextComponent>();
			});


		// sprite

		// UI?

		// camera?

		// Transform Component
		RegisterComponent<TransformComponent>(registry, "TransformComponent",
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
		RegisterComponent<VelocityComponent>(registry, "VelocityComponent",
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

		// Tag Component
		RegisterComponent<TagComponent>(registry, "TagComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<TagComponent>();
			});

		// Audio Component
		RegisterComponent<AudioComponent>(registry, "AudioComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<AudioComponent>();
			});

		// Timer Component
		RegisterComponent<TimerComponent>(registry, "TimerComponent",
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

		RegisterComponent<UIComponent>(registry, "UIComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<UIComponent>();
			});

		RegisterComponent<InputComponent>(registry, "InputComponent",
			[](EntityHandle& handle, const Properties& data)
			{
				auto& component = handle.GetComponent<InputComponent>();

				// temp...
				component.InputStates.insert({ Hi_Engine::eKey::Key_W, false });
				component.InputStates.insert({ Hi_Engine::eKey::Key_A, false });
				component.InputStates.insert({ Hi_Engine::eKey::Key_S, false });
				component.InputStates.insert({ Hi_Engine::eKey::Key_D, false });
			});
	}

	void RegisterEvents(EventRegistryService& registry)
	{
	}
}