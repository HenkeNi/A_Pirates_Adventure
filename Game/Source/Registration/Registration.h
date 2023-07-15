#pragma once

class SystemManager;
class SceneManager;

namespace Registration
{
	void RegisterComponents();

	void RegisterBlueprints();

	void RegisterSystems(SystemManager& aSystemManager);

	void RegisterScenes(SceneManager& aSceneManager, SystemManager& aSystemManager);	
}