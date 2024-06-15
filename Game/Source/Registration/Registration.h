#pragma once

class EntityFactory;
class ECS;
class SystemManager;
class SceneManager;

namespace Registration
{
	void RegisterComponents(EntityFactory& factory);

	void RegisterSystems(SystemManager& systemManager);

	void RegisterBlueprints();

	void RegisterScenes(SceneManager& sceneManager, ECS& ecs);	
}