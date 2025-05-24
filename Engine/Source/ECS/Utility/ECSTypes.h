#pragma once
#include "Utility/IDGenerator.h"
#include "Utility/TypeTraits.h"
#include "Utility/DataStructures/SparseSet.h"
#include "Entity.h"
#include <functional>
#include <variant>
#include <memory>
#include <bitset>

namespace Hi_Engine
{
	constexpr std::size_t MaxSystems = 64;
	constexpr std::size_t MaxEntities = 100000; // 5000;
	constexpr std::uint8_t MaxComponents = 64;

#define INVALID_ENTITY -1 // ??

	using ComponentID = std::uint8_t;
	using SystemID = std::uint8_t;

	struct ComponentTag final {};
	struct SystemTag final {};

	template <ComponentType T>
	ComponentID GetComponentID()
	{
		return static_cast<ComponentID>(IDGenerator<ComponentTag>::GetID<T>());
	}

	class System;
	template <DerivedFrom<System> T>
	SystemID GetSystemID()
	{
		return static_cast<SystemID>(IDGenerator<SystemTag>::GetID<T>());
	}

	using Signature = std::bitset<MaxComponents>;

	template <ComponentType T>
	using ComponentContainer = SparseSet<std::decay_t<T>, EntityID>;
	
	using ComponentManagerMap = std::unordered_map<ComponentID, std::unique_ptr<class IComponentManager>>;


	//using Property = std::variant<bool, int, float, double, std::string, FVector2, FVector3, FVector4, IVector2, IVector3, IVector4>;
	//using ComponentProperties = std::unordered_map<std::string, Property>;
}