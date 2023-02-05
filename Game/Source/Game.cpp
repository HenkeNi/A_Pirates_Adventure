#include "Pch.h"
#include "Game.h"
#include "Scenes/Scenes.hpp"
#include "Factories/GameObjectFactory.h"


Game::Game()
{
}

Game::~Game()
{
}

void Game::OnUpdate(float aDeltaTime)
{
	m_sceneManager.Update(aDeltaTime);
}

void Game::OnLateUpdate(float aDeltaTime)
{
	m_sceneManager.LateUpdate(aDeltaTime);
}

void Game::OnDraw()
{
	m_sceneManager.Draw();
}

void Game::OnCreate()
{
	SetupScenes();
	LoadBlueprints();
}

void Game::OnDestroy()
{
	m_sceneManager.Clear();
}

void Game::SetupScenes()
{
	SceneManagerProxy proxy{ m_sceneManager };

	m_sceneManager.Register(std::make_unique<TitleScene>(proxy),	eSceneType::Title);
	m_sceneManager.Register(std::make_unique<LoadingScene>(proxy),  eSceneType::Loading);
	m_sceneManager.Register(std::make_unique<MenuScene>(proxy),		eSceneType::Menu);
	m_sceneManager.Register(std::make_unique<GameScene>(proxy),		eSceneType::Game);
	m_sceneManager.Register(std::make_unique<PauseScene>(proxy),	eSceneType::Pause);

	m_sceneManager.Init({ eSceneType::Game, eSceneType::Menu, eSceneType::Loading, eSceneType::Title });
}

void Game::LoadBlueprints()
{
	auto& factory = GameObjectFactory::GetInstance();

	factory.LoadBlueprints("../Bin/Assets/Json/Blueprints/Blueprints_Enemy.json");
	factory.LoadBlueprints("../Bin/Assets/Json/Blueprints/Blueprints_UI.json");
	factory.LoadBlueprints("../Bin/Assets/Json/Blueprints/Blueprints_Scene.json");
}