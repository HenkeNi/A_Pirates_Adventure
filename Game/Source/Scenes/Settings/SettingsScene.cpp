#include "Pch.h"
#include "SettingsScene.h"


//SettingsScene::SettingsScene(Hi_Engine::ECSCoordinator& ecs)
//	: Scene{ ecs }
//{
//}
//
//SettingsScene::~SettingsScene()
//{
//}

void SettingsScene::OnUpdate(float deltaTime)
{

}

void SettingsScene::OnEnter()
{
	// Music component instead?
	//Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>("night_ambience", true);
}

void SettingsScene::OnExit()
{
	// m_ecs.DestroyAllEntities();

	//Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::StopSoundEvent>("night_ambience");
}
