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

	// Change json; button prefab, separate between prefabs adn  scene entities

	auto* cursor = m_entityManager.Create("Mouse_Cursor");
	


	auto* play = m_entityManager.Create("play_button");
	auto* buttonComponent = play->GetComponent<ButtonComponent>();
	buttonComponent->OnClick = [&]() { m_sharedContext.SceneManager.Pop(); };
	 play->GetComponent<TransformComponent>()->CurrentPos = { 0.f, 0.f };
	
	//auto* quit = m_entityManager.Create("quit_button");
	// quit->GetComponent<TransformComponent>()->CurrentPos = { 2.f, 2.f };
	//quit->GetComponent<ButtonComponent>()->OnClick = [&]() { Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::TerminationEvent>(); };
	//quit->GetComponent<ButtonComponent>()->OnClick = [&]() { m_sharedContext.SceneManager.Clear();  }; // OR SEND EVENT?

	auto* background = m_entityManager.Create("main_background");

	auto* title = m_entityManager.Create("title_text");


	auto* camera = m_entityManager.Create("Camera");
	camera->GetComponent<TransformComponent>()->CurrentPos = { 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->TargetOffset = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->TargetID = play->GetID();
	camera->GetComponent<CameraComponent>()->ShouldCull = false;
}

void MenuScene::OnExit()
{
}