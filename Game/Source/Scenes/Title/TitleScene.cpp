#include "Pch.h"
#include "TitleScene.h"
 
TitleScene::TitleScene(Hi_Engine::ServiceRegistry& registry)
	: Scene{ registry }
{
}

void TitleScene::OnUpdate(float deltaTime)
{
}

void TitleScene::OnEnter()
{
}

void TitleScene::OnExit() 
{
	m_world.DestroyAllEntities();

	// Destroy all systems? or do in Scene?
}