#pragma once

#include "../../Core/Math/Vectors/Vector.hpp" // temp...

#include <bitset>
#include <functional>
#include <variant>

namespace Hi_Engine
{
	constexpr std::size_t MaxSystems = 64;
	constexpr std::size_t MaxEntities = 5000;
	constexpr std::uint8_t MaxComponents = 64;


#define INVALID_ENTITY -1 // ??

	// type aliases
	using Entity = int;
	using ComponentID = std::uint8_t;
	using ComponentIDs = std::unordered_map<std::type_index, ComponentID>;
	// using ComponentArrays = std::unordered_map<std::type_index, std::unique_ptr<class IComponentArray>>;// void ptr instead?
	using Signature = std::bitset<MaxComponents>;
	using Signatures = std::unordered_map<std::string, Signature>;
	using Property = std::variant<bool, int, float, double, std::string, FVector2, FVector3, FVector4, IVector2, IVector3, IVector4>;
	using ComponentProperties = std::unordered_map<std::string, Property>;
	
	//using ComponentRegistry = std::unordered_map<std::string, struct ComponentRegistryEntry>; // make into class?

	//struct ComponentRegistryEntry
	//{
	//	std::function<void(Entity)> AddComponent;
	//	std::function<void(Entity, const ComponentProperties&)> InitializeComponent;
	//};

	struct CallbackRegistry
	{
		inline static std::unordered_map<const char*, std::function<void(Entity)>> Callbacks; // Maybe in Timer/Button Component (or system), or separate Callback/Action component?
	};
}