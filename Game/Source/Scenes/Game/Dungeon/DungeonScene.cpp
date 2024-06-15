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
	std::cout << "Updating dungeon\n";
}

void DungeonScene::LateUpdate(float deltaTime)
{
}

void DungeonScene::Draw() const
{
	// m_map.Draw();
}

void DungeonScene::OnEnter()
{
}

void DungeonScene::OnExit()
{
}
