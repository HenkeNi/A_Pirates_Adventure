#include "Pch.h"
#include "Game.h"
#include "Registration/Registration.h"
#include "Scenes/Scene.h"
#include "Entities/EntityManager.h"
//#include <../Hi_Engine.h>

Game::Game()
{
}

Game::~Game()
{
}

void Game::OnUpdate(float deltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();

	if (activeScene.expired())
		return;

	if (auto scene = activeScene.lock())
	{
		scene->Update(deltaTime);
	}
}

void Game::OnLateUpdate(float deltaTime)
{
	std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();

	if (activeScene.expired())
		return;
	
	if (auto scene = activeScene.lock())
	{
		scene->LateUpdate(deltaTime);
	}
}

void Game::OnDraw()
{
	std::weak_ptr<const Scene> activeScene = m_sceneManager.GetActiveScene();

	if (activeScene.expired())
		return;

	if (auto scene = activeScene.lock())
	{
		scene->Draw();
	}
}

void Game::OnCreate()
{
	LoadResources(); // Maybe each scene should load the data they need?
	m_ecs.Init();

	// put in ECS?
	Registration::RegisterComponents(m_ecs.GetEntityManager().GetFactory());
	Registration::RegisterBlueprints();
	Registration::RegisterSystems(m_ecs.GetSystemManager());  // ECS register system?
	Registration::RegisterScenes(m_sceneManager, m_ecs);

	m_ecs.GetSystemManager().Init(&m_ecs.GetEntityManager()); // FIX!!!

	m_sceneManager.Init({ eScene::Game, eScene::Menu, eScene::Title });
	m_sceneManager.TransitionToScene(eScene::Title);
}

void Game::OnDestroy()
{
	m_sceneManager.Clear();
	m_ecs.Shutdown();
}

void Game::LoadResources()
{
	Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Textures2.json");
	//Hi_Engine::ResourceHolder<Hi_Engine::GLSLShader>::GetInstance().LoadResources("../Engine/Assets/Json/Resources/Shaders.json");
	Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Fonts.json");
	Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().LoadResources("../Game/Assets/Json/Audio/Audio.json");
}