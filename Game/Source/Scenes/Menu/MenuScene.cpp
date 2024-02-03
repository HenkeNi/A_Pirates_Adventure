#include "Pch.h"
#include "MenuScene.h"


MenuScene::MenuScene(SharedContext aContext)
	: Scene{ aContext }
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Update(float aDeltaTime)
{
	m_sharedContext.SystemManager.Update(aDeltaTime);
}

void MenuScene::LateUpdate(float aDeltaTime)
{
}

void MenuScene::Draw() const
{
	m_sharedContext.SystemManager.Draw();
}

void MenuScene::OnEnter()
{
	auto& systemManager = m_sharedContext.SystemManager;
	systemManager.Init(&m_entityManager);

	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");

	auto* play = m_entityManager.Create("play_button");

	auto* camera = m_entityManager.Create("Camera");
	camera->GetComponent<TransformComponent>()->CurrentPos = { 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->TargetOffset = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->TargetID = play->GetID();
}

void MenuScene::OnExit()
{
}