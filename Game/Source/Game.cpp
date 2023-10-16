#include "Pch.h"
#include "Game.h"
#include "Registration/Registration.h"
#include "Scene.h"
#include <Core/Resources/ResourceHolder.hpp>

Game::Game()
{
}

Game::~Game()
{
}

void Game::OnUpdate(float aDeltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->Update(aDeltaTime);
	}

	//m_sceneManager.Update(aDeltaTime);
	m_systemManager.Update(aDeltaTime);	 // DONT update here as well?!
}

void Game::OnLateUpdate(float aDeltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->LateUpdate(aDeltaTime);
	}

	// m_sceneManager.LateUpdate(aDeltaTime);
	m_systemManager.LateUpdate(aDeltaTime);
}

void Game::OnDraw()
{
	std::weak_ptr<const Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->Draw();
	}

	//m_sceneManager.Draw();
	m_systemManager.Draw();
}

void Game::OnCreate()
{
	LoadResources();

	Registration::RegisterComponents();
	Registration::RegisterBlueprints();
	Registration::RegisterSystems(m_systemManager);
	Registration::RegisterScenes(m_sceneManager, m_systemManager);

	std::bitset<(int)eScene::Count> scenes(0);
	scenes[(int)eScene::Title] = 1;
	scenes[(int)eScene::Game] = 1;

	m_sceneManager.Init(scenes);
	
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();
	if (auto scene = activeScene.lock())
	{
		scene->OnEnter();
	}
	//scenes.set((int)eScene::Title);
	//scenes.set((int)eScene::Game);
	//scenes != (1 << (int)eScene::Title);
	//scenes != (1 << (int)eScene::Game);


	// m_sceneManager.Init((int)eScene::Game); // Rename, set active scnee?
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
	//Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().FetchAll("../Game/Assets/Json/Resources/Textures.json");
	Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Textures2.json");
	// Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().FetchAll("../Game/Assets/Json/Resources/Subtextures.json");
	
	Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().LoadResources("../Engine/Assets/Json/Resources/Shaders.json");
	Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Fonts.json");
}
