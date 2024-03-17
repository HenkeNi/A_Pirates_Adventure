#pragma once

class SystemManager;
class SceneManager;

namespace Registration
{
	void RegisterComponents();

	void RegisterBlueprints();

	void RegisterSystems(SystemManager& systemManager);

	void RegisterScenes(SceneManager& sceneManager, SystemManager& systemManager);	
}