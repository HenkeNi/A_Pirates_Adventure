#pragma once

//class Hi_Engine::ECSCoordinator;
class SceneManager;

namespace Registration
{
	void RegisterComponents();
	//void RegisterComponents(Hi_Engine::ECSCoordinator& ecs);

	void RegisterSystems(SceneManager& sceneManager);
	//void RegisterSystems(Hi_Engine::ECSCoordinator& ecs);

	void RegisterScenes(SceneManager& sceneManager);

	void RegisterCallbacks();
	//void RegisterScenes(SceneManager& sceneManager, Hi_Engine::ECSCoordinator& ecs);
}