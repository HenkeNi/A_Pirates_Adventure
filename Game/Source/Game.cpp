#include "Pch.h"
#include "Game.h"
//#include "Scenes/Scene.h"
//#include "SceneTypes.h"
#include "Registration/Registration.h"
// #include <>

Game::Game()
	//: m_sceneManager{} // , m_ecs{ std::make_unique<ECS>() }
{
}

Game::~Game()
{
}

void Game::OnUpdate(float deltaTime)
{
	//std::weak_ptr<Scene> activeScene = m_sceneManager.GetActiveScene();

	//if (auto scene = activeScene.lock())
	//{
	//	scene->Update(deltaTime);
	//}
}

void Game::OnCreate()
{
	LoadResources();

	auto& sceneManager = m_serviceRegistry->Get<Hi_Engine::SceneManager>();
	
	Registration::RegisterScenes(sceneManager);


	// Consider; read scenes from file?

	// m_ecs->Init();
	
	// auto ecs = Hi_Engine::ServiceLocator::GetECS().lock();

	//Registration::RegisterComponents(*ecs);
	//Registration::RegisterSystems(m_sceneManager);

	// m_ecs->LoadBlueprints();

	//m_sceneManager.Init({ eScene::Game, eScene::Menu, eScene::Title });
	//m_sceneManager.TransitionToScene(eScene::Title);
}

void Game::OnDestroy()
{
	// m_sceneManager.Shutdown();
	// m_ecs->Shutdown();
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