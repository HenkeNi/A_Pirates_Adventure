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

	auto weakSceneRegistry = m_serviceRegistry->TryGetWeak<Hi_Engine::SceneRegistry>();
	auto weakSystemRegistry = m_serviceRegistry->TryGetWeak<Hi_Engine::SystemRegistry>();

	if (auto sharedSceneRegistry = weakSceneRegistry.lock())
		Registration::RegisterScenes(*sharedSceneRegistry);

	// Consider; read scenes from file?
	auto& sceneManager = m_serviceRegistry->Get<Hi_Engine::SceneManager>();

	//auto systemRegistry = m_serviceRegistry->TryGetWeak<Hi_Engine::SystemRegistry>();



	sceneManager.Emplace<TitleScene>(Hi_Engine::RegistryContext{ weakSceneRegistry, weakSystemRegistry });

	sceneManager.Init<TitleScene>();
	sceneManager.TransitionTo<TitleScene>();
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
 	Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Textures2.json");
//	Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().LoadResources("../Game/Assets/Json/Resources/Fonts.json"); // do in engine!
	Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().LoadResources("../Game/Assets/Json/Audio/Audio.json");
}