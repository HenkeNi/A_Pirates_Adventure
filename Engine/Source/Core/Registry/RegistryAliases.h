#pragma once
#include "TypeRegistry.h"
#include "../Scene/SceneTypes.h"
#include "../../ECS/Utility/ECSTypes.h"
#include "RegistryEntries.h"

namespace Hi_Engine
{
	// Do i need to include / forward declare entries?

	using ComponentRegistry = TypeRegistry<ComponentRegistryEntry, ComponentID>;
	using SystemRegistry = TypeRegistry<SystemRegistryEntry, SystemID>;
	using SceneRegistry = TypeRegistry<SceneRegistryEntry, SceneID>;
}