#pragma once
#include "../../Scene.h"
#include "../Map/Map.h"


class OverworldScene : public Scene
{
public:
	OverworldScene(SharedContext aContext);
	~OverworldScene();

	void Update(float aDeltaTime)			  override;
	void LateUpdate(float aDeltaTime)		  override;
	void Draw()							const override;

	void OnCreated()						  override;
	void OnEnter()							  override;
	void OnExit()							  override;

private:
	Map	 m_map;
};
