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
	m_systemManager.Update(aDeltaTime);
}

void DungeonScene::LateUpdate(float aDeltaTime)
{
	m_systemManager.LateUpdate(aDeltaTime);
}

void DungeonScene::Draw() const
{
	m_map.Draw();
	m_systemManager.Draw();
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
