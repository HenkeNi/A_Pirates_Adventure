#include "Pch.h"
#include "DungeonScene.h"


DungeonScene::DungeonScene(SharedContext context)
	: Scene{ context }
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

void DungeonScene::OnCreated()
{
}

void DungeonScene::OnEnter()
{
}

void DungeonScene::OnExit()
{
}
