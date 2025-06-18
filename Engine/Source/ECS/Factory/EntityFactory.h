#pragma once
#include "../ECS/Utility/ECSTypes.h"
#include "Registry/RegistryAliases.h"
//#include "../Utility/EntityHandle.h"

namespace Hi_Engine
{
	class PrefabRegistry;
	class EntityHandle;
	class World;

	class EntityFactory
	{
	public:
		EntityFactory(World& world, std::weak_ptr<const PrefabRegistry> prefabRegistry, std::weak_ptr<const ComponentRegistry> componentRegistry);

		// dont mark with nodiscard?
		std::optional<EntityHandle> CreateFromPrefab(World& world, const std::string& name); // bool notify = true

	private:
		// use Registry struct?
		std::weak_ptr<const PrefabRegistry> m_prefabRegistry;
		std::weak_ptr<const ComponentRegistry> m_componentRegistry; // non const?

		World& m_world;
	};
}