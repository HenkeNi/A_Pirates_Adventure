#include "Pch.h"
#include "OverworldScene.h"
#include "Systems/SystemManager.h"
#include "ECS/ECS.h"
#include "Entities/EntityManager.h"
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
	m_ecs.Update(deltaTime);
}

void OverworldScene::LateUpdate(float deltaTime)
{
	m_ecs.LateUpdate(deltaTime);
}

void OverworldScene::Draw() const
{
	m_ecs.Draw();
}

void OverworldScene::OnEnter()
{
	auto* audio = &Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource("ocean_ambience");
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>(audio);

	PostMaster::GetInstance().SendMessage({ eMessage::GameStarted, true }); // Todo; FIX
}

void OverworldScene::OnExit()
{
	auto* audio = &Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource("ocean_ambience");

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::StopSoundEvent>(audio);
	//Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::StopSoundEvent>("ocean_ambience");
}
