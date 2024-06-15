#pragma once
#include "../../Scene.h"

// Rename GameMenu or InGameMenu? CraftingsMenu...
class InventoryScene : public Scene
{
public:
	InventoryScene(ECS& ecs);
	~InventoryScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnEnter()							  override;
	void OnExit()							  override;
};