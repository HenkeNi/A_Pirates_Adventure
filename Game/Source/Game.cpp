#include "Pch.h"
#include "Game.h"
#include "Registration/Registration.h"
#include "Title/TitleScene.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::OnUpdate(float deltaTime)
{
}

void Game::OnCreate()
{
	LoadResources();

	if (!m_serviceRegistry)
	{
		assert(false && "[Game::OnCreate] - ServiceRegistry not valid!");
		return;
	}

	auto weakSceneRegistry = m_serviceRegistry->TryGetWeak<Hi_Engine::SceneRegistryService>();

	if (auto sceneRegistry = weakSceneRegistry.lock())
		Registration::RegisterScenes(*sceneRegistry);

	auto weakSystemRegistry = m_serviceRegistry->TryGetWeak<Hi_Engine::SystemRegistryService>();

	if (auto systemRegistry = weakSystemRegistry.lock())
		Registration::RegisterSystems(*systemRegistry);


	// Consider; read scenes from file?
	auto& sceneService = m_serviceRegistry->Get<Hi_Engine::SceneService>();

	//auto systemRegistry = m_serviceRegistry->TryGetWeak<Hi_Engine::SystemRegistry>();


	// maybe just pass service registry?
	sceneService.Emplace<TitleScene>(*m_serviceRegistry);

	sceneService.Init<TitleScene>();
	sceneService.TransitionTo<TitleScene>();
	//Registration::RegisterComponents(*ecs);
	//Registration::RegisterSystems(m_sceneManager);

	// m_ecs->LoadBlueprints();

	//m_sceneManager.Init({ eScene::Game, eScene::Menu, eScene::Title });
	//m_sceneManager.TransitionToScene(eScene::Title);
}

void Game::OnDestroy()
{
}

//void Game::RegisterScenes()
//{
//	auto& sceneManager = m_serviceRegistry->Get<Hi_Engine::SceneManager>();
//	sceneManager.Emplace<Hi_Engine::TitleScene>("TitleScene");
//}

void Game::LoadResources()
{
 	//Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Textures2.json");
//	Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Fonts.json"); // do in engine!
	//Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().LoadResources("../Game/Assets/Json/Audio/Audio.json");
}