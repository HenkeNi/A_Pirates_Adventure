#pragma once
#include "../ECS/Utility/ECSTypes.h"
#include "Registry/RegistryAliases.h"
//#include "../Utility/EntityHandle.h"

namespace Hi_Engine
{
	class PrefabRegistryService;
	class EntityHandle;
	class World;

	class EntityFactory
	{
	public:
		EntityFactory(World& world, std::weak_ptr<const PrefabRegistryService> prefabRegistry, std::weak_ptr<const ComponentRegistryService> componentRegistry);

		// dont mark with nodiscard?
		std::optional<EntityHandle> CreateFromPrefab(World& world, const std::string& name); // bool notify = true

	private:
		// use Registry struct?
		std::weak_ptr<const PrefabRegistryService> m_prefabRegistry;
		std::weak_ptr<const ComponentRegistryService> m_componentRegistry; // non const?

		World& m_world;
	};
}