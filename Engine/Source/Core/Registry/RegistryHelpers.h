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
	class ServiceRegistry;

	template <DerivedFrom<System> T, Callable<World&, ServiceRegistry&> Creator>
	void RegisterSystem(SystemRegistryService& registry, const std::string& name, Creator&& creationFunc)
	{
		const SystemID id = GetSystemID<T>();
		registry.Register<T>(name, id, name, true, id, std::type_index(typeid(T)), std::forward<Creator>(creationFunc));
	}

	class Scene;
	template <DerivedFrom<Scene> T>
	void RegisterScene(SceneRegistryService& registry, const std::string& name, const std::filesystem::path& path, const std::string& description = "")
	{
		const SceneID id = GetSceneID<T>();

		registry.Register<T>(name, id, id, path, name, description);
	}

	class EventService;
	//template <DerivedFrom<BaseEvent> T, Callable<EventService&, const Properties&> DispatchFunc>
	template <typename T, typename DispatchFunc>
	void RegisterEvent(EventRegistryService& registry, const std::string& name, DispatchFunc&& func)
	{
		const EventID id = GetEventID<T>();

		// ( name - id )  Entry data: name, dispathfunc
		registry.Register<T>(name, id, name, std::forward<DispatchFunc>(func));
	}
}

