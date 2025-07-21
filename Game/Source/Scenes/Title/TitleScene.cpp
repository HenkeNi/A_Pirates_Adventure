#include "Pch.h"
#include "TitleScene.h"
 
TitleScene::TitleScene(Hi_Engine::ServiceRegistry& registry)
	: Scene{ registry }
{
}

void TitleScene::OnUpdate(float deltaTime)
{
	int x = 20;
}

void TitleScene::OnEnter()
{
 	int x = 20;
}

void TitleScene::OnExit() 
{
	m_world.DestroyAllEntities();


	// Destroy all systems?
	m_world.RemoveAllSystems();
}