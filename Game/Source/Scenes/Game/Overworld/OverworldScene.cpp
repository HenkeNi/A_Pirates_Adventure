#include "Pch.h"
#include "OverworldScene.h"
#include "Systems/Base/System.h"
#include "ECS/ECS.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"


OverworldScene::OverworldScene(ECS& ecs)
	: Scene{ ecs }
{
}

OverworldScene::~OverworldScene()
{
}

void OverworldScene::Update(float deltaTime)
{
	for (auto& systemWeak : m_systems)
	{
		if (auto system = systemWeak.lock())
		{
			system->Update(deltaTime);
		}
	}
}

void OverworldScene::LateUpdate(float deltaTime)
{
	for (auto& systemWeak : m_systems)
	{
		if (auto system = systemWeak.lock())
		{
			system->LateUpdate(deltaTime);
		}
	}
}

void OverworldScene::Draw() const
{
	for (auto& systemWeak : m_systems)
	{
		if (auto system = systemWeak.lock())
		{
			system->Draw();
		}
	}
}

void OverworldScene::OnEnter()
{
	Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>("ocean_ambience");

	PostMaster::GetInstance().SendMessage({ eMessage::GameStarted, true }); // Todo; FIX
}

void OverworldScene::OnExit()
{
	Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::StopSoundEvent>("ocean_ambience");
}
