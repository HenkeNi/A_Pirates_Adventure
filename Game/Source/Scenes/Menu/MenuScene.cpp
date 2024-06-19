#include "Pch.h"
#include "MenuScene.h"
#include "Systems/SystemManager.h"
#include "ECS/ECS.h"
#include "Entities/EntityManager.h"


MenuScene::MenuScene(ECS& ecs)
	: Scene{ ecs }
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Update(float deltaTime)
{
	m_ecs.GetSystemManager().Update(deltaTime);
}

void MenuScene::LateUpdate(float deltaTime)
{
}

void MenuScene::Draw() const
{
	m_ecs.GetSystemManager().Draw();
}

void MenuScene::OnEnter()
{
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>("theme_drunken_sailor");
}

void MenuScene::OnExit()
{
	m_ecs.GetEntityManager().DestroyAll();

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::StopSoundEvent>("theme_drunken_sailor");
}