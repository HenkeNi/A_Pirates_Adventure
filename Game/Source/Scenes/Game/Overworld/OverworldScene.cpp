#include "Pch.h"
#include "OverworldScene.h"
#include "Systems/Map/MapGenerationSystem.h"

OverworldScene::OverworldScene(Hi_Engine::ServiceRegistry& registry)
	: Scene{ registry }
{
}

OverworldScene::~OverworldScene()
{
}

void OverworldScene::OnUpdate(float deltaTime)
{
}

void OverworldScene::OnEnter()
{
	auto& mapGenerationSystem = m_world.GetSystem<MapGenerationSystem>();
	mapGenerationSystem.SetFactory(&m_entityFactory);
	

	PostMaster::GetInstance().SendMessage({ eMessage::GameStarted, true });
}

void OverworldScene::OnExit()
{
}

// TODO; always destroy systems? leaving them alive will allow them to listen for events!