#pragma once
#include <cstdint>
#include "Utility/TypeTraits.h"
#include "Utility/IDGenerator.h"

namespace Hi_Engine
{
	struct SceneTag final {};

	using SceneID = uint32_t;

	class Scene;

	template <DerivedFrom<Scene> T>
	SceneID GetSceneID()
	{
		return IDGenerator<SceneTag>::GetID<T>();
	}
}