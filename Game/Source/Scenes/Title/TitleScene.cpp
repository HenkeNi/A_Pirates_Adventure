#include "Pch.h"
#include "TitleScene.h"
#include "ECS/ECS.h"
#include "Entities/EntityManager.h"
#include "Systems/SystemManager.h"


TitleScene::TitleScene(ECS& ecs)
	: Scene{ ecs }
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float deltaTime)  // TODO; listen for any button press - add trigger componment to background?
{
	// TEMP => use component instead??
	/*static float elapsedTime = 0.f;

	elapsedTime += deltaTime;
	if (elapsedTime >= 5.f)
	{
		m_sharedContext.SceneManager.Pop();
	}*/
	m_ecs.GetSystemManager().Update(deltaTime);
}

void TitleScene::LateUpdate(float deltaTime) {}

void TitleScene::Draw() const 
{
	m_ecs.GetSystemManager().Draw();
}

void TitleScene::OnEnter()
{

	// TODO; scene loads needed systems??

	// TODO; load in relevant systems..
	// TODO; Start audio?

	// INput component, and a trigger component? can skip by clicking...

	// Should factory itself load blueprints (listen for scene change)? maybe load scene specific "blueprints"?
	//m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json"); // load blueprints once??

	// auto* inputListener = m_entityManager.CreateResources()
}

void TitleScene::OnExit() 
{
	m_ecs.GetEntityManager().DestroyAll();
	// TODO; Clear entities...
}