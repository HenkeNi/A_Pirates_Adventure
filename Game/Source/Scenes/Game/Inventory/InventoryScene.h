#pragma once
#include "../../Scene.h"

// Rename GameMenu or InGameMenu? CraftingsMenu...
class InventoryScene : public Scene
{
public:
	//InventoryScene(Hi_Engine::ECSCoordinator& ecs);
	//~InventoryScene();

	void Update(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};