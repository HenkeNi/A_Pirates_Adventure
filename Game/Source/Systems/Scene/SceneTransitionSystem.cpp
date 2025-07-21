#include "Pch.h"
#include "SceneTransitionSystem.h"


#include "Game/GameScene.h" // TEMP


SceneTransitionSystem::SceneTransitionSystem(World& world, SceneService& sceneService, EventService& eventService/*, SceneRegistryService& sceneRegistry*/)
	: System{ world, Hi_Engine::eUpdatePhase::Update }, m_sceneService{ sceneService }, m_eventService{ eventService }//, m_sceneRegistryService{ sceneRegistry }
{
	m_eventService.Subscribe(this);
}

SceneTransitionSystem::~SceneTransitionSystem()
{
	m_eventService.Unsubscribe(this);
}

void SceneTransitionSystem::Update(float deltaTime)
{
}

void SceneTransitionSystem::OnEvent(SceneEvent& event)
{
	const auto& sceneType = event.GetType();

	// TEMP (todo; fix so SceneRegistry (and all TypeRegistry classes, uses string as optional key(?))


	if (sceneType == "GameScene")
	{
		auto id = Hi_Engine::GetSceneID<GameScene>();
		m_sceneService.TransitionTo(id);
	}

	//m_sceneService.TransitionTo();
	//int x = 20;
}