#include "Pch.h"
#include "EntityFactory.h"
#include "../ECS/Core/EntityManager.h"
#include "Prefab/PrefabRegistry.h"
#include "../ECS/Utility/EntityHandle.h"
#include "../Registry/ComponentRegistry.h"


namespace Hi_Engine
{
	/*EntityFactory::EntityFactory(std::weak_ptr<const PrefabRegistry> registry)
		: m_prefabRegistry{ registry }
	{
	}*/


	//void InitializeComponent(struct TransformComponent* component, const Prefab& prefab)
	//{
	//	// component->xPosition = std::get<int>(prefab); // sudo code..
	//}


	void EntityFactory::Initialize(std::weak_ptr<const PrefabRegistry> registry)
	{
		m_prefabRegistry = registry;
	}

	std::optional<EntityHandle> EntityFactory::CreateFromPrefab(World& world, const std::string& name)
	{
		if (auto prefabRegistry = m_prefabRegistry.lock())
		{
			const auto* prefab = prefabRegistry->TryGetPrefab(name);

			if (!prefab)
			{
				Logger::LogWarning("Failed to find prefab with name: " + name);
				return std::nullopt;
			}

			auto entityHandle = world.CreateEntity();

			if (!entityHandle.has_value())
			{
				return std::nullopt;
				Logger::LogWarning("Failed to create entity!");
			}

			auto& entity = entityHandle.value();

			auto& componentRegistry = ECSRegistry::GetComponentRegistry();

			for (const auto& [componentName, properties] : prefab->Data)
			{
				auto componentMeta = componentRegistry.GetComponentRegistryEntry(componentName.c_str());

				componentMeta.AddComponentFunc(entity);
				componentMeta.InitFunc(entity, properties);

			}

			//world.CreateEntity
		}

		return std::nullopt;
	}
}


//	std::optional<Entity> EntityFactory::CreateFromPrefab(const char* name) const
//	{
//		std::optional<Entity> entity = m_entityManager.Create();
//
//		if (!entity.has_value())
//			return std::nullopt;
//
//		auto prefab = m_prefabs.find(name);
//
//		assert(prefab != m_prefabs.end() && "Prefab not found");
//
//		const auto& componentProperties = prefab->second.GetComponentProperties();
//		for (const auto& [component, properties] : componentProperties)
//		{
//			const auto& data = m_componentRegistry.GetComponentDataByName(component.c_str());
//			// TODO; call add component function
//
//			//auto itr = m_componentRegistry.find(component);
//
//			//if (itr == m_componentRegistry.end())
//			//	continue;
//
//
//			// itr->second.AddComponent(entity.value());
//
//			if (!properties.empty()) // Todo, also put checks in ComponentInitailizer!
//			{
//				//itr->second.InitializeComponent(entity.value(), properties);
//
//				// TODO; initialize
//			}
//		}
//
//		return entity;
//	}
//
//	std::optional<Entity> EntityFactory::CreateFromJson(const rapidjson::Value& value)
//	{
//		const char* id = value["entity_id"].GetString();
//		std::optional<Entity> entity = CreateFromPrefab(id); // dont call this? or refactor function?? or fine since json only overrides some values?
//
//		if (!entity.has_value())
//			return std::nullopt;
//
//		if (value.HasMember("components_data"))
//		{
//			for (const auto& component : value["components_data"].GetArray())
//			{
//				ComponentProperties componentProperties;
//
//				for (const auto& [key, value] : component["properties"].GetObj())
//				{
//					Property property = EntityPrefab::ParseProperty(value);
//					componentProperties.insert({ key.GetString(), property });
//				}
//
//				const auto& componentType = component["type"].GetString();
//
//				const auto& data = m_componentRegistry.GetComponentDataByName(componentType);
//
//				// TODO; call init function...
//
//				//auto itr = m_componentRegistry.find(componentType);
//
//				//if (itr != m_componentRegistry.end())
//				//{
//				//	//itr->second.InitializeComponent(entity.value(), componentProperties);
//				//}
//				//else
//				//{
//				//	std::cerr << "[EntityFactory::CreateFromJson] - couldn't find component type " << componentType << "\n";
//				//}
//
//			}
//		}
//
//		return entity;
//	}
//}
