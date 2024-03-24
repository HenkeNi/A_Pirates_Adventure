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
	/*static float elapsedTime = 0.f;

	elapsedTime += deltaTime;
	if (elapsedTime >= 5.f)
	{
		m_sharedContext.SceneManager.Pop();
	}*/

	m_sharedContext.SystemManager.Update(deltaTime);
}

void TitleScene::LateUpdate(float deltaTime) {}

void TitleScene::Draw() const 
{
	m_sharedContext.SystemManager.Draw();
}

void TitleScene::OnCreated()
{
}

void TitleScene::OnEnter()
{
	auto& systemManager = m_sharedContext.SystemManager;
	systemManager.Init(&m_entityManager);

	// TODO; scene loads needed systems??

	// TODO; load in relevant systems..
	// TODO; Start audio?

	// INput component, and a trigger component? can skip by clicking...

	// Should factory itself load blueprints (listen for scene change)? maybe load scene specific "blueprints"?
	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");

	// auto* inputListener = m_entityManager.CreateResources()
}

void TitleScene::OnExit() 
{
	m_entityManager.DestroyAll();
	// TODO; Clear entities...
}