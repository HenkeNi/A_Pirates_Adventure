#pragma once
#include <../Services/Scene/Scene.h>


class DungeonScene : public Hi_Engine::Scene
{
public:
	DungeonScene(Hi_Engine::ServiceRegistry& registry);

	void OnUpdate(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};

