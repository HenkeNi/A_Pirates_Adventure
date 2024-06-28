#include "Pch.h"
#include "OverworldScene.h"
#include "Systems/SystemManager.h"
#include "ECS/ECS.h"
#include "Entities/EntityManager.h"


OverworldScene::OverworldScene(ECS& ecs)
	: Scene{ ecs }
{
}

OverworldScene::~OverworldScene()
{
}

void OverworldScene::Update(float deltaTime)
{
	m_ecs.GetSystemManager().Update(deltaTime);
}

void OverworldScene::LateUpdate(float deltaTime)
{
	m_ecs.GetSystemManager().LateUpdate(deltaTime);
}

void OverworldScene::Draw() const
{
	m_ecs.GetSystemManager().Draw();
}

void OverworldScene::OnEnter()
{
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>("ocean_ambience");

	auto& entityManager = m_ecs.GetEntityManager();

	auto* player = entityManager.Create("player");
	// player->GetComponent<SpriteComponent>()->Pivot = { -0.5f, -0.5f };

	// auto* cursor = entityManager.Create("mouse_cursor");
	// auto* time = entityManager.Create("world_time");

	auto* weapon = entityManager.Create("rusty_sword");
	auto* skeleton = entityManager.Create("skeleton");
	auto* crab = entityManager.Create("crab");


	// Camera => do in camera system??
	auto* camera = entityManager.FindFirst<CameraComponent>();
	camera->GetComponent<TransformComponent>()->CurrentPos = { 0.f, 0.f };
	camera->GetComponent<CameraComponent>()->TargetOffset = { 0.f, 0.f }; // each scene has own camera? different projection matrixes?
	camera->GetComponent<CameraComponent>()->TargetOffset = { -700.f, -400.f }; // each scene has own camera? different projection matrixes?
	camera->GetComponent<CameraComponent>()->TargetID = entityManager.FindFirst<PlayerControllerComponent>()->GetID();

	PostMaster::GetInstance().SendMessage({ eMessage::GameStarted, true }); 	// FIX
}

void OverworldScene::OnExit()
{
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::StopSoundEvent>("ocean_ambience");
}
