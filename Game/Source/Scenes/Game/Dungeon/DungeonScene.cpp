#include "Pch.h"
#include "DungeonScene.h"


DungeonScene::DungeonScene(SharedContext aContext)
	: Scene{ aContext }
{
}

DungeonScene::~DungeonScene()
{
}

void DungeonScene::Update(float aDeltaTime)
{
	std::cout << "Updating dungeon\n";
}

void DungeonScene::LateUpdate(float aDeltaTime)
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
