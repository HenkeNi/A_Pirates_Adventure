#include "Pch.h"
#include "Game.h"
#include "Scenes/Scenes.h"
#include "../Generated/Generated.h"
#include <Core/Resources/ResourceHolder.hpp>


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
	EntityManager::RegisterComponentBuilders();

	LoadResources();
	SetupScenes();

	//m_gameWorld.Init();

	//Generated::RegisterComponents();
	//Generated::RegisterPrototypes();	

	MapInput();
}

void Game::OnDestroy()
{
	m_sceneManager.Clear();
}

void Game::SetupScenes()
{
	SceneManagerProxy proxy{ m_sceneManager };

	m_sceneManager.Register(std::make_unique<GameScene>(SharedContext{ proxy }), eScene::Game);
	//m_sceneManager.Register(std::make_unique<LoadingScene>(proxy),  eScene::Loading);
	//m_sceneManager.Register(std::make_unique<MenuScene>(proxy),		eScene::Menu);
	//m_sceneManager.Register(std::make_unique<PauseScene>(proxy),	eScene::Pause);
	//m_sceneManager.Register(std::make_unique<TitleScene>(proxy),	eScene::Title);
		
	//m_sceneManager.Init(eScene::Game | eScene::Menu | eScene::Loading | eScene::Title);
	m_sceneManager.Init((int)eScene::Game);
}

void Game::LoadResources()
{
	Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().FetchAll("../Assets/Json/Resources/Textures.json");
	Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().FetchAll("../../Engine/Assets/Json/Resources/Textures.json");
}

void Game::MapInput() // or MapControlls? // Rename ConfigureInput??
{
	//Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_W, new MoveCommand{  0.f, -1.f });
	//Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_A, new MoveCommand{ -1.f,  0.f });
	//Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_S, new MoveCommand{  0.f,  1.f });
	//Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_D, new MoveCommand{  1.f,  0.f });
}