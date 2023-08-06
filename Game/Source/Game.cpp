#include "Pch.h"
#include "Game.h"
// #include "Scenes/Scenes.h"
#include "Registration/Registration.h"
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
	m_systemManager.Update(aDeltaTime);
}

void Game::OnLateUpdate(float aDeltaTime)
{
	m_sceneManager.LateUpdate(aDeltaTime);
	m_systemManager.LateUpdate(aDeltaTime);
}

void Game::OnDraw()
{
	m_sceneManager.Draw();
	m_systemManager.Draw();
}

void Game::OnCreate()
{
	LoadResources();

	Registration::RegisterComponents();
	Registration::RegisterBlueprints();
	Registration::RegisterSystems(m_systemManager);
	Registration::RegisterScenes(m_sceneManager, m_systemManager);

	m_sceneManager.Init((int)eScene::Game); // Rename, set active scnee?
	//m_sceneManager.Init((int)eScene::Title); // Rename, set active scnee?
	//m_sceneManager.Init((int)eScene::Game | (int)eScene::Title); // Rename, set active scnee?
	//m_sceneManager.Init(eScene::Game | eScene::Menu | eScene::Loading | eScene::Title);
}

void Game::OnDestroy()
{
	m_systemManager.Clear();
	m_sceneManager.Clear();
}

void Game::LoadResources()	// Todo, do in Registration?
{
	Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().FetchAll("../Game/Assets/Json/Resources/Textures.json");
	Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().FetchAll("../Engine/Assets/Json/Resources/Shaders.json");
	Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().FetchAll("../Game/Assets/Json/Resources/Fonts.json");
}
