#pragma once

class ECS;
class SceneManager;

namespace Registration
{
	//void RegisterComponents(ECS& ecs);

	void RegisterSystems(ECS& ecs);

	void RegisterScenes(SceneManager& sceneManager, ECS& ecs);	
}