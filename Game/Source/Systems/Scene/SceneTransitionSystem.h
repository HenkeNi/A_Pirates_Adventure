#pragma once
#include <../Source/ECS/Systems/System.h>

namespace Hi_Engine
{
	class World;
	class SceneService;
	class SceneEvent;
	class EventService;
	//class SceneRegistryService;
}

using Hi_Engine::World;
using Hi_Engine::SceneService;
//using Hi_Engine::SceneRegistryService;
using Hi_Engine::SceneEvent;
using Hi_Engine::EventService;
using Hi_Engine::System;
using Hi_Engine::EventListener;
using Hi_Engine::eUpdatePhase;

class SceneTransitionSystem : public System, public EventListener
{
public:
	SceneTransitionSystem(World& world, SceneService& sceneService, EventService& eventService/*, SceneRegistryService& sceneRegistry*/);
	~SceneTransitionSystem();

	void Update(float deltaTime) override;
	void OnEvent(SceneEvent& event) override;

private:
	// TOOD; store weak tprs?
	SceneService& m_sceneService;
	//SceneRegistryService& m_sceneRegistryService;
	EventService& m_eventService;
};