#include "Pch.h"
#include "Game.h"
#include "Scenes/Scenes.h"
//#include "Factories/GameObjectFactory.h"
#include "Commands/MoveCommand.h"
//#include "Generated/Generated.h"
#include "../Generated/Generated.h"

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
	SetupScenes();		// do after registering comps/prototpyes??	

	Generated::RegisterComponents();	// HERE??
	Generated::RegisterPrototypes();

	MapInput();
}

void Game::OnDestroy()
{
	m_sceneManager.Clear();
}

void Game::SetupScenes()
{
	SceneManagerProxy proxy{ m_sceneManager };

	m_sceneManager.Register(std::make_unique<GameScene>(proxy),		eSceneType::Game);
	m_sceneManager.Register(std::make_unique<LoadingScene>(proxy),  eSceneType::Loading);
	m_sceneManager.Register(std::make_unique<MenuScene>(proxy),		eSceneType::Menu);
	m_sceneManager.Register(std::make_unique<PauseScene>(proxy),	eSceneType::Pause);
	m_sceneManager.Register(std::make_unique<TitleScene>(proxy),	eSceneType::Title);
		
	m_sceneManager.Init({ eSceneType::Game, eSceneType::Menu, eSceneType::Loading, eSceneType::Title });
}

void Game::MapInput()
{
	Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_W, new MoveCommand{  0.f, -1.f });
	Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_A, new MoveCommand{ -1.f,  0.f });
	Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_S, new MoveCommand{  0.f,  1.f });
	Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_D, new MoveCommand{  1.f,  0.f });
}