#include "Pch.h"
#include "Game.h"
#include "Scenes/Scene.h"
#include "Registration/Registration.h"
#include "ECS/ECS.h"


Game::Game()
	: m_sceneManager{}, m_ecs{ std::make_unique<ECS>() }
{
}

Game::~Game()
{
}

void Game::OnUpdate(float deltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();

	if (auto scene = activeScene.lock())
	{
		scene->Update(deltaTime);
	}
}

void Game::OnLateUpdate(float deltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();

	if (auto scene = activeScene.lock())
	{
		scene->LateUpdate(deltaTime);
	}
}

void Game::OnDraw()
{
	std::weak_ptr<const Scene> activeScene = m_sceneManager.GetActiveScene();

	if (auto scene = activeScene.lock())
	{
		scene->Draw();
	}
}

void Game::OnCreate()
{
	LoadResources(); // Maybe each scene should load the data they need?
	m_ecs->Init();
	
	Registration::RegisterComponents(*m_ecs);
	Registration::RegisterSystems(*m_ecs);
	Registration::RegisterScenes(m_sceneManager, *m_ecs);

	m_ecs->LoadBlueprints();

	m_sceneManager.Init({ eScene::Game, eScene::Menu, eScene::Title });
	m_sceneManager.TransitionToScene(eScene::Title);
}

void Game::OnDestroy()
{
	m_sceneManager.Shutdown();
	m_ecs->Shutdown();
}

void Game::LoadResources()
{
 	Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Textures2.json");
	Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Fonts.json"); // do in engine!
	Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().LoadResources("../Game/Assets/Json/Audio/Audio.json");
}