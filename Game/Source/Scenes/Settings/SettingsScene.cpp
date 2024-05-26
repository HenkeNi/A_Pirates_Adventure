#include "Pch.h"
#include "SettingsScene.h"
#include "Systems/SystemManager.h"


SettingsScene::SettingsScene(SharedContext context)
	: Scene{ context }
{
}

SettingsScene::~SettingsScene()
{
}

void SettingsScene::Update(float deltaTime)
{
	m_sharedContext.SystemManager.Update(deltaTime);
}

void SettingsScene::LateUpdate(float deltaTime)
{
}

void SettingsScene::Draw() const
{
	m_sharedContext.SystemManager.Draw();
}

void SettingsScene::OnEnter()
{
	auto& systemManager = m_sharedContext.SystemManager;
	systemManager.Init(&m_entityManager);

	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");

	// Todo; PlaySound(sound identifier in resourceholder)
	auto& sound = Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource("night_ambience"); // TODO; read from json...
	//Hi_Engine::ServiceLocator::GetAudioController().lock()->PlaySound(sound);
}

void SettingsScene::OnExit()
{
	m_entityManager.DestroyAll();

	auto& sound = Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource("night_ambience");
	//Hi_Engine::ServiceLocator::GetAudioController().lock()->StopSound(sound);
}
