#include "Pch.h"
#include "DungeonScene.h"
#include "Systems/SystemManager.h"
#include "ECS/ECS.h"


DungeonScene::DungeonScene(ECS& ecs)
	: Scene{ ecs }
{
}

DungeonScene::~DungeonScene()
{
}

void DungeonScene::Update(float deltaTime)
{
}

void DungeonScene::LateUpdate(float deltaTime)
{
}

void DungeonScene::Draw() const
{
}

void DungeonScene::OnEnter()
{
}

void DungeonScene::OnExit()
{
}
