#include "Pch.h"
#include "SettingsScene.h"
#include "Systems/Base/System.h"
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
	for (auto& systemWeak : m_systems)
	{
		if (auto system = systemWeak.lock())
		{
			system->Update(deltaTime);
		}
	}
}

void SettingsScene::Draw() const
{
	for (auto& systemWeak : m_systems)
	{
		if (auto system = systemWeak.lock())
		{
			system->Draw();
		}
	}
}

void SettingsScene::OnEnter()
{
	// Music component instead?
	Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>("night_ambience");
}

void SettingsScene::OnExit()
{
	m_ecs.DestroyAllEntities();

	Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::StopSoundEvent>("night_ambience");
}
