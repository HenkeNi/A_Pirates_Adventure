#pragma once
#include "TypeRegistry.h"
#include "../../Services/Scene/SceneTypes.h"
#include "../../Services/Event/EventTypes.h"
#include "../../ECS/Utility/ECSTypes.h"
#include "RegistryEntries.h"

namespace Hi_Engine
{
	// Do i need to include / forward declare entries?

	using ComponentRegistryService = TypeRegistry<ComponentRegistryEntry, ComponentID>;
	using SystemRegistryService = TypeRegistry<SystemRegistryEntry, SystemID>;
	using SceneRegistryService = TypeRegistry<SceneRegistryEntry, SceneID>;
	using EventRegistryService = TypeRegistry<EventRegistryEntry, EventID>;
}