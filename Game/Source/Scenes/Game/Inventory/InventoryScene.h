#pragma once
#include "../../Scene.h"


class InventoryScene : public Scene
{
public:
	InventoryScene(SharedContext context);
	~InventoryScene();

	void Update(float deltaTime)			  override;
	void LateUpdate(float deltaTime)		  override;
	void Draw()							const override;

	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};