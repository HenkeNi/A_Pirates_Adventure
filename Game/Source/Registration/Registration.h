#pragma once

//class EntityFactory;
class ECS;
//class SystemManager;
class SceneManager;

namespace Registration
{
	//void RegisterComponents(EntityFactory& factory);
	void RegisterComponents(ECS& ecs);

	void RegisterSystems(ECS& ecs);

	void RegisterBlueprints(ECS& ecs);

	void RegisterScenes(SceneManager& sceneManager, ECS& ecs);	
}