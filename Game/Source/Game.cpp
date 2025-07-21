#include "Pch.h"
#include "Game.h"
#include "Registration/Registration.h"
#include "Title/TitleScene.h"

#include "Game/GameScene.h" // or construct SCenes!?

Game::Game()
{
}

Game::~Game()
{
}

void Game::OnUpdate(float deltaTime)
{
}

void Game::OnCreated()
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

	auto weakComponentRegistry = m_serviceRegistry->TryGetWeak<Hi_Engine::ComponentRegistryService>();

	if (auto componentRegistry = weakComponentRegistry.lock())
		Registration::RegisterComponents(*componentRegistry);

	// Consider; read scenes from file?
	auto& sceneService = m_serviceRegistry->Get<Hi_Engine::SceneService>();

	//auto systemRegistry = m_serviceRegistry->TryGetWeak<Hi_Engine::SystemRegistry>();

	// maybe just pass service registry?
	sceneService.Emplace<TitleScene>(*m_serviceRegistry);
	sceneService.Emplace<GameScene>(*m_serviceRegistry);

	sceneService.SetActiveScenes<TitleScene>();
	sceneService.TransitionTo<TitleScene>(); // Do in init?
 }

void Game::OnDestroyed()
{
}

void Game::LoadResources()
{
	// Prefabs
	auto& prefabRegistry = m_serviceRegistry->Get<Hi_Engine::PrefabRegistryService>();

	for (const auto& filePath : Hi_Engine::Utils::GetFilesWithExtension("../Assets/Prefabs", ".json"))
	{
		prefabRegistry.LoadPrefabs(filePath);
	}

	// Fonts

	// Icons (set window icon)

	// Textures
	Hi_Engine::TextureLoader::LoadFromJson(m_serviceRegistry->Get<Hi_Engine::TextureAssetService>(), m_serviceRegistry->Get<Hi_Engine::SubtextureAssetService>(), "../Assets/Textures/Textures2.json");

	// Audio
	Hi_Engine::AudioLoader::LoadFromJson(m_serviceRegistry->Get<Hi_Engine::AudioService>(), m_serviceRegistry->Get<Hi_Engine::AudioAssetService>(), "../Assets/Audio/Audio.json");
}