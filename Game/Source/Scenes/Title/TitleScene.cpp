#include "Pch.h"
#include "TitleScene.h"
#include "ECS/ECS.h"


TitleScene::TitleScene(ECS& ecs)
	: Scene{ ecs }
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float deltaTime)
{
	m_ecs.Update(deltaTime);
}

void TitleScene::Draw() const 
{
	m_ecs.Draw();
}

void TitleScene::OnEnter()
{
}

void TitleScene::OnExit() 
{
	m_ecs.DestroyAllEntities(); // here?
}