#pragma once
#include "../Utility/TypeTraits.h"
#include "../ECS/Systems/System.h"

namespace Hi_Engine
{
	template <typename RegistryEntry>
	struct RegistryTraits;

	struct ComponentRegistryEntry;

	template <>
	struct RegistryTraits<ComponentRegistryEntry>
	{
		template <typename T>
		static constexpr bool IsValidType = ComponentType<T>;
	};

	//class System;
	struct SystemRegistryEntry;

	template <>
	struct RegistryTraits<SystemRegistryEntry>
	{
		template <typename T>
		static constexpr bool IsValidType = DerivedFrom<T, System>; // Correct? check other use cases of this concpept
	};

	class Scene;
	struct SceneRegistryEntry;

	template <>
	struct RegistryTraits<SceneRegistryEntry>
	{
		template <typename T>
		static constexpr bool IsValidType = DerivedFrom<T, Scene>; // need to include scene?
	};

	struct PrefabRegistryEntry;

	template <>
	struct RegistryTraits<PrefabRegistryEntry>
	{
		template <typename T>
		static constexpr bool IsValidType = true; // ?? maybe check for something?
	};
}