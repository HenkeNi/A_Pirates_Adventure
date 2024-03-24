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
}

void SettingsScene::OnExit()
{
	m_entityManager.DestroyAll();
}
