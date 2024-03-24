#include "Pch.h"
#include "MenuScene.h"
#include "Systems/SystemManager.h"


MenuScene::MenuScene(SharedContext context)
	: Scene{ context }
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Update(float deltaTime)
{
	m_sharedContext.SystemManager.Update(deltaTime);
}

void MenuScene::LateUpdate(float deltaTime)
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

	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json"); // load differnet blueprints depding on scene? OR read scene specific entities


	/*auto* quit = m_entityManager.Create("quit_button");
	quit->GetComponent<TransformComponent>()->CurrentPos = { 0.1f, 0.1f };
	quit->GetComponent<ButtonComponent>()->OnClick = [&]() { Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::TerminationEvent>(); };*/
	//quit->GetComponent<ButtonComponent>()->OnClick = [&]() { m_sharedContext.SceneManager.Clear();  }; // OR SEND EVENT?

	//auto* camera = m_entityManager.Create("camera");
	// camera->GetComponent<CameraComponent>()->TargetID = play->GetID();
	//camera->GetComponent<CameraComponent>()->ShouldCull = false;
}

void MenuScene::OnExit()
{
	m_entityManager.DestroyAll();
}