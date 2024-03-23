#include "Pch.h"
#include "TitleScene.h"
#include "Components/Core/CoreComponents.h"
#include "Systems/SystemManager.h"


TitleScene::TitleScene(SharedContext context)
	: Scene{ context }
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float deltaTime) 
{
	// TEMP => use component instead??
	static float elapsedTime = 0.f;

	elapsedTime += deltaTime;
	if (elapsedTime >= 5.f)
	{
		m_sharedContext.SceneManager.Pop();
	}

	m_sharedContext.SystemManager.Update(deltaTime);
}

void TitleScene::LateUpdate(float deltaTime) {}

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

	// Should factory itself load blueprints (listen for scene change)? maybe load scene specific "blueprints"?
	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");


	// trigger component?
	// TODO; load in relevant systems..
	// TODO; Load in new entities...



	auto* background = m_entityManager.Create("image");
	background->GetComponent<TransformComponent>()->Scale = { 2.f, 2.f };
	background->GetComponent<SpriteComponent>()->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "title_image", 0, 0 });
	auto* transformComponent = background->GetComponent<TransformComponent>();
	// transformComponent->Pivot = { 0.5f, 0.5f };
	transformComponent->Scale *= 2.5f;
	transformComponent->Scale.x *= 2.f;
	transformComponent->CurrentPos.y = 0.f;


	// INput component, and a trigger component...





	// Add triiger componnet??

	// TODO; read from json?? Title_text.json...
	auto* title = m_entityManager.Create("title_text");
	title->GetComponent<TransformComponent>()->CurrentPos.x = 1400.f * 0.5f;
	title->GetComponent<TransformComponent>()->Pivot.x = -0.5f;
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