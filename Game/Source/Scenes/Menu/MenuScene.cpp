#include "Pch.h"
#include "MenuScene.h"

//
//MenuScene::MenuScene(Hi_Engine::ECSCoordinator& ecs)
//	: Scene{ ecs }
//{
//}
//
//MenuScene::~MenuScene()
//{
//}

void MenuScene::Update(float deltaTime)
{

}

void MenuScene::OnEnter()
{
	//Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>("theme_drunken_sailor");
}

void MenuScene::OnExit()
{
	// m_ecs.DestroyAllEntities();
	//Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::StopSoundEvent>("theme_drunken_sailor");
}