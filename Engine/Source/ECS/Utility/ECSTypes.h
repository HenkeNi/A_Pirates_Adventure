#pragma once

#include "../../Core/Math/Vectors/Vector.hpp" // temp...

#include <bitset>
#include <functional>
#include <variant>

#include "Utility/TypeTraits.h"
#include "Utility/DataStructures/SparseSet.h"
#include "Entity.h"
//#include <type_traits>

#include <memory>

namespace Hi_Engine
{
	constexpr std::size_t MaxSystems = 64;
	constexpr std::size_t MaxEntities = 100000; // 5000;
	constexpr std::uint8_t MaxComponents = 64;

#define INVALID_ENTITY -1 // ??

	using ComponentID = std::uint8_t;
	//using ComponentIDs = std::unordered_map<std::type_index, ComponentID>;

	using Signature = std::bitset<MaxComponents>;

	//using Property = std::variant<bool, int, float, double, std::string, FVector2, FVector3, FVector4, IVector2, IVector3, IVector4>;
	//using ComponentProperties = std::unordered_map<std::string, Property>;
	
	template <ComponentType T>
	using ComponentContainer = SparseSet<std::decay_t<T>, EntityID>;

	using ComponentManagerMap = std::unordered_map<ComponentID, std::unique_ptr<class IComponentManager>>;
}