#pragma once
#include "TypeRegistry.h"
#include "RegistryAliases.h"


#include "../Utility/TypeTraits.h"
#include "../../Services/Scene/SceneTypes.h"
#include "../../ECS/Utility/ECSTypes.h"
#include "../../ECS/Utility/EntityHandle.h"
#include "../../Services/Resource/PrefabRegistryService.h"// neede for prefab data?



//#include "ECS/World/World.h" // ?????
//#include "Services/ServiceRegistry.h"

namespace Hi_Engine
{
	template <ComponentType T, Callable<EntityHandle&, const Properties&> InitFunc>
	void RegisterComponent(ComponentRegistryService& registry, const std::string& name, InitFunc&& func)
	{
		const ComponentID id = GetComponentID<T>();

		registry.Register<T>(name, id, name, sizeof(T), alignof(T), id, std::forward<InitFunc>(func), 
			[](EntityHandle& handle) 
			{
				handle.AddComponent<T>();
			});
	}

	class System;

	// When used?? calls below??
	template <DerivedFrom<System> T>
	void RegisterSystem(SystemRegistryService& registry, const std::string& name)
	{
		RegisterSystem<T>(registry, name, [](World& world, ServiceRegistry& registry) { return std::make_unique<T>(world); });
	}

	//class World;
	template <DerivedFrom<System> T, Callable<World&, ServiceRegistry&> Creator>
	void RegisterSystem(SystemRegistryService& registry, const std::string& name, Creator&& creationFunc)
	{
		const SystemID id = GetSystemID<T>();
		//registry.Register<T>(name, id, name, true, id, [](class World& world) { return std::make_unique<T>(world); });
		registry.Register<T>(name, id, name, true, id, std::forward<Creator>(creationFunc));

	}

	class Scene;
	template <DerivedFrom<Scene> T>
	void RegisterScene(SceneRegistryService& registry, const std::string& name, const std::filesystem::path& path, const std::string& description = "")
	{
		const SceneID id = GetSceneID<T>();

		registry.Register<T>(name, id, id, path, name, description);
	}
}

