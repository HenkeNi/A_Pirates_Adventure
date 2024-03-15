#pragma once
#include "../../Scene.h"


class InventoryScene : public Scene
{
public:
	InventoryScene(SharedContext aContext);
	~InventoryScene();

	void Update(float aDeltaTime)			  override;
	void LateUpdate(float aDeltaTime)		  override;
	void Draw()							const override;

	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};