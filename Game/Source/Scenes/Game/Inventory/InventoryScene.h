#pragma once
#include <../Services/Scene/Scene.h>

// Rename GameMenu or InGameMenu? CraftingsMenu...
class InventoryScene : public Hi_Engine::Scene
{
public:
	//InventoryScene(Hi_Engine::ECSCoordinator& ecs);
	//~InventoryScene();

	void OnUpdate(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};