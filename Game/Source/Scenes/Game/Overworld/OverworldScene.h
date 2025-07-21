#pragma once
#include <../Services/Scene/Scene.h>


class OverworldScene : public Hi_Engine::Scene
{
public:
	OverworldScene(Hi_Engine::ServiceRegistry& registry);
	~OverworldScene();

	// TEMP
	OverworldScene(const OverworldScene&) = delete;
	OverworldScene(OverworldScene&&) = delete;

	OverworldScene& operator=(const OverworldScene&) = delete;
	OverworldScene& operator=(OverworldScene&&) = delete;

	void OnUpdate(float deltaTime)			  override;
	void OnEnter()							  override;
	void OnExit()							  override;
};