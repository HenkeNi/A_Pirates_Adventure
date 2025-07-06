#pragma once

// or static initialization for components and system?
namespace Hi_Engine::EngineSetup
{
	void RegisterSystems(SystemRegistryService& registry);

	void RegisterComponents(ComponentRegistryService& registry);

	void RegisterEvents(EventRegistryService& registry);
}