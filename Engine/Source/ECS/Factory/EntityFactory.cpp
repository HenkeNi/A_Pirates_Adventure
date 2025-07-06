#include "Pch.h"
#include "EntityFactory.h"
#include "../ECS/Core/EntityManager.h"
#include "Services/Resource/PrefabRegistryService.h"
#include "../ECS/Utility/EntityHandle.h"


namespace Hi_Engine
{
	EntityFactory::EntityFactory(World& world, std::weak_ptr<const PrefabRegistryService> prefabRegistry, std::weak_ptr<const ComponentRegistryService> componentRegistry)
		: m_world{ world }, m_prefabRegistry{ prefabRegistry }, m_componentRegistry{ componentRegistry }
	{
	}

	std::optional<EntityHandle> EntityFactory::CreateFromPrefab(World& world, const std::string& name)
	{
		auto prefabRegistry = m_prefabRegistry.lock();

		if (!prefabRegistry)
		{
			Logger::LogWarning("[EntityFactory::CreateFromPrefab] - invalid PrefabRegistry");
			return std::nullopt;
		}

		auto componentRegistry = m_componentRegistry.lock();

		if (!componentRegistry)
		{
			Logger::LogWarning("[EntityFactory::CreateFromPrefab] - invalid ComponentRegistry");
			return std::nullopt;
		}

		const auto* prefab = prefabRegistry->TryGetPrefab(name);

		if (!prefab)
		{
			Logger::LogWarning("[EntityFactory::CreateFromPrefab] - Failed to find prefab: " + name);
			return std::nullopt;
		}

		auto optionalEntityHandle = world.CreateEntity();

		if (!optionalEntityHandle.has_value())
		{
			Logger::LogWarning("[EntityFactory::CreateFromPrefab] - Failed to create entity!");
			return std::nullopt;
		}

		auto& entityHandle = optionalEntityHandle.value();

		for (const auto& [componentName, properties] : prefab->ComponentProperties)
		{
			const auto& componentEntry = componentRegistry->Get(componentName);

			componentEntry.AddComponentFunc(entityHandle);
			componentEntry.InitFunc(entityHandle, properties);
		}

		return entityHandle;
	}
}
