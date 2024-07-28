#include "Pch.h"
#include "SettingsScene.h"
#include "ECS/ECS.h"


SettingsScene::SettingsScene(ECS& ecs)
	: Scene{ ecs }
{
}

SettingsScene::~SettingsScene()
{
}

void SettingsScene::Update(float deltaTime)
{
	m_ecs.Update(deltaTime);
}

void SettingsScene::Draw() const
{
	m_ecs.Draw();
}

void SettingsScene::OnEnter()
{
	// TODO; read from json...?
	//Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>("night_ambience");
}

void SettingsScene::OnExit()
{
	m_ecs.DestroyAllEntities();

	//Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::StopSoundEvent>("night_ambience");
}
