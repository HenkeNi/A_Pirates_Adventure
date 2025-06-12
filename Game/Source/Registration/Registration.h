#pragma once
//#include <Utility/RegistryEntries.h>

//class Hi_Engine::ECSCoordinator;

//namespace Hi_Engine
//{
//	template <typename RegistryEntry, typename ID>
//	class TypeRegistry;
//
//	using SceneRegistry = TypeRegistry<SceneRegistryEntry, SceneID>;
//}

namespace Registration
{
	void RegisterComponents();

	//void RegisterSystems(Hi_Engine::ServiceRegistry& registry); // maybe each scene?

	void RegisterScenes(Hi_Engine::SceneRegistry& registry);

	// void RegisterCallbacks();
}