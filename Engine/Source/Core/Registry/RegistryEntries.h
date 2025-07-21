#pragma once
#include "../../Services/Scene/SceneTypes.h"
#include "../../Services/Resource/PrefabRegistryService.h"// Fix this! needed for Prefab::ComponentData
#include "../../ECS/Utility/ECSTypes.h"


#include <filesystem> // temp

namespace Hi_Engine
{
	class EntityHandle;
	
	struct ComponentRegistryEntry
	{
		std::string Name;
		std::size_t Size; // size in bytes
		std::size_t Alignment;
		ComponentID ID;

		// Pass world instead?
		std::function<void(EntityHandle& handle, const Properties& data)> InitFunc; // rename Initializer?
		//std::function<void(EntityHandle& handle, const decltype(Prefab::ComponentProperties)& data)> InitFunc; // rename Initializer?
		std::function<void(EntityHandle& handle)> AddComponentFunc; // reanem Create function?

		// std::function<void()> // store serialization func, accept rapidjson Value object?
		// std::function<void(void*)> destructor;        
	};

	struct SystemRegistryEntry
	{
		//const char* DisplayName;
		std::string DisplayName;

		bool IsEnabledByDefault = true;
		SystemID ID;
		std::type_index Type;

		std::function<std::unique_ptr<System>(class World& world, class ServiceRegistry& registry)> CreatorFunction;
		// Update order? enum / tag for type (render, physics, logic)? Dependencies
		// Execution / Update phase: PreUpdate, Update, PostUpdate
	};

	struct SceneRegistryEntry
	{
		SceneID ID;
		std::filesystem::path JsonPath;

		std::string DisplayName;
		std::string Description;

		// thumbnail path? priority?
	};

	class EventService;
	struct EventRegistryEntry
	{
		/*EventRegistryEntry(const std::string& name, const std::function<void(EventService&, const Properties&)>& func)
			: Name{ name }, DispatchFunc{ func }
		{}*/

		std::string Name;
		//std::function<void(class EventService&, const Properties&)> DispatchFunc; // value?
		std::function<void(EventService&, const Properties&)> DispatchFunc; // value?
		//std::function<void(const std::unordered_map<std::string, PropertyValue>& params)> DispatchFunc;
	};

	// store events??
}