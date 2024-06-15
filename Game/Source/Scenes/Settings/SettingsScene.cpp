#include "Pch.h"
#include "SettingsScene.h"
#include "Systems/SystemManager.h"
#include "Entities/EntityManager.h"
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
	m_ecs.GetSystemManager().Update(deltaTime);
}

void SettingsScene::LateUpdate(float deltaTime)
{
}

void SettingsScene::Draw() const
{
	m_ecs.GetSystemManager().Draw();
}

void SettingsScene::OnEnter()
{
	// Todo; PlaySound(sound identifier in resourceholder)
	auto& sound = Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource("night_ambience"); // TODO; read from json...
	//Hi_Engine::ServiceLocator::GetAudioController().lock()->PlaySound(sound);
}

void SettingsScene::OnExit()
{
	m_ecs.GetEntityManager().DestroyAll();

	auto& sound = Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource("night_ambience");
	//Hi_Engine::ServiceLocator::GetAudioController().lock()->StopSound(sound);
}
