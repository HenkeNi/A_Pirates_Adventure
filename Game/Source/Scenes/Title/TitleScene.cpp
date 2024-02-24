#include "Pch.h"
#include "TitleScene.h"
#include "Components/Core/CoreComponents.h"


TitleScene::TitleScene(SharedContext aContext)
	: Scene{ aContext }
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float aDeltaTime) 
{
	// TEMP => use component instead??
	static float elapsedTime = 0.f;

	elapsedTime += aDeltaTime;
	if (elapsedTime >= 5.f)
	{
		m_sharedContext.SceneManager.Pop();
	}

	m_sharedContext.SystemManager.Update(aDeltaTime);
}

void TitleScene::LateUpdate(float aDeltaTime) {}

void TitleScene::Draw() const 
{
	m_sharedContext.SystemManager.Draw();
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

	// Should factory itself load blueprints (listen for scene change)?
	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");


	// trigger component?
	// TODO; load in relevant systems..
	// TODO; Load in new entities...



	auto* background = m_entityManager.Create("title_background");
	auto* transformComponent = background->GetComponent<TransformComponent>();
	transformComponent->Scale *= 2.5f;
	transformComponent->Scale.x *= 2.f;
	transformComponent->CurrentPos.y = 0.f;


	// INput component, and a trigger component...





	// Add triiger componnet??

	// TODO; read from json?? Title_text.json...
	auto* title = m_entityManager.Create("title_text");

	// auto* inputListener = m_entityManager.CreateResources()

	auto* camera = m_entityManager.Create("Camera");
	camera->GetComponent<TransformComponent>()->CurrentPos = { 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->TargetOffset = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->TargetID = background->GetID();
}

void TitleScene::OnExit() 
{
	m_entityManager.DestroyAll();
	// TODO; Clear entities...
}