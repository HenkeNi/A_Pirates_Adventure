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

void TitleScene::Update(float deltaTime)
{
	m_ecs.GetSystemManager().Update(deltaTime);
}

void TitleScene::LateUpdate(float deltaTime) {}

void TitleScene::Draw() const 
{
	m_ecs.GetSystemManager().Draw();
}

void TitleScene::OnEnter()
{
}

void TitleScene::OnExit() 
{
	m_ecs.GetEntityManager().DestroyAll();
}