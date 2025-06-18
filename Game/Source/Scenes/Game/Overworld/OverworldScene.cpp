#include "Pch.h"
#include "OverworldScene.h"


//OverworldScene::OverworldScene(Hi_Engine::ECSCoordinator& ecs)
//	: Scene{ ecs }
//{
//}
//
//OverworldScene::~OverworldScene()
//{
//}

void OverworldScene::OnUpdate(float deltaTime)
{
}

void OverworldScene::OnEnter()
{
	//Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>("ocean_ambience", true);

	//PostMaster::GetInstance().SendMessage({ eMessage::GameStarted, true }); // Todo; FIX
}

void OverworldScene::OnExit()
{
	//Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::StopSoundEvent>("ocean_ambience");
}
