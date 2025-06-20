#pragma once
#include "TypeRegistry.h"
#include "../Utility/TypeTraits.h"
#include "../Scene/SceneTypes.h"
#include "../../ECS/Utility/ECSTypes.h"
#include "../../ECS/Utility/EntityHandle.h"
#include "../../Prefab/PrefabRegistry.h" // neede for prefab data?
#include "RegistryAliases.h"

#include "../World/World.h" // ?????

namespace Hi_Engine
{
	template <ComponentType T, Callable<EntityHandle&, const Properties&> InitFunc>
	void RegisterComponent(ComponentRegistry& registry, const std::string& name, InitFunc&& func)
	{
		const ComponentID id = GetComponentID<T>();

		registry.Register<T>(name, id, name, sizeof(T), alignof(T), id, std::forward<InitFunc>(func), 
			[](EntityHandle& handle) 
			{
				handle.AddComponent<T>();
			});
	}

	class System;

	template <DerivedFrom<System> T>
	void RegisterSystem(SystemRegistry& registry, const std::string& name)
	{
		RegisterSystem<T>(registry, name, [](World& world, ServiceRegistry& registry) { return std::make_unique<T>(world); });
	}

	//class World;
	template <DerivedFrom<System> T, Callable<World&, ServiceRegistry&> Creator>
	void RegisterSystem(SystemRegistry& registry, const std::string& name, Creator&& creationFunc)
	{
		const SystemID id = GetSystemID<T>();
		//registry.Register<T>(name, id, name, true, id, [](class World& world) { return std::make_unique<T>(world); });
		registry.Register<T>(name, id, name, true, id, std::forward<Creator>(creationFunc));

	}

	class Scene;
	template <DerivedFrom<Scene> T>
	void RegisterScene(SceneRegistry& registry, const std::string& name, const std::filesystem::path& path, const std::string& description = "")
	{
		const SceneID id = GetSceneID<T>();

		registry.Register<T>(name, id, id, path, name, description);
	}
}

