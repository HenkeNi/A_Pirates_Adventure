#pragma once
#include "../../Scene/SceneTypes.h"
#include "../Prefab/PrefabRegistry.h" // Fix this! needed for Prefab::ComponentData
#include "../../ECS/Utility/ECSTypes.h"


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
		std::function<void(EntityHandle& handle, const Prefab::ComponentData& data)> InitFunc; // rename Initializer?
		std::function<void(EntityHandle& handle)> AddComponentFunc;

		// std::function<void()> // store serialization func, accept rapidjson Value object?
		// std::function<void(void*)> destructor;        
	};

	struct SystemRegistryEntry
	{
		const char* DisplayName;

		bool IsEnabledByDefault = true;
		SystemID ID;

		std::function<std::unique_ptr<System>(class World* world)> CreatorFunction;
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
}