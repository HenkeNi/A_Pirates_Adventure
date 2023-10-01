#include "Pch.h"
#include "TitleScene.h"


TitleScene::TitleScene(SharedContext aContext)
	: Scene{ aContext }
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float aDeltaTime) 
{
}

void TitleScene::LateUpdate(float aDeltaTime) {}

void TitleScene::Draw() const
{
}

//void TitleScene::Draw() const {}

void TitleScene::OnCreated()
{
	// TODO; Register for events...
}

void TitleScene::OnEnter()
{
	auto& systemManager = m_sharedContext.SystemManager;
	systemManager.Init(&m_entityManager);

	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");


	// trigger component?

	// TODO; load in relevant systems..


	// TODO; Load in new entities...

	auto background = m_entityManager.CreateResources("title_background");
	
	// Add triiger componnet??


	auto camera = m_entityManager.CreateResources("Camera");
	camera->GetComponent<TransformComponent>()->CurrentPos = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->TargetOffset = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->TargetID = background->GetID();

}

void TitleScene::OnExit() 
{
	// TODO; Clear entities...
}