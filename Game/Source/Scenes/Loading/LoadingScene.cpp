#include "Pch.h"
#include "LoadingScene.h"
#include "Systems/SystemManager.h"
#include "ECS/ECS.h"


LoadingScene::LoadingScene(ECS& ecs)
	: Scene{ ecs }
{
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::Update(float deltaTime)
{
}

void LoadingScene::Draw() const
{
}

void LoadingScene::OnEnter()
{
}

void LoadingScene::OnExit()
{
}