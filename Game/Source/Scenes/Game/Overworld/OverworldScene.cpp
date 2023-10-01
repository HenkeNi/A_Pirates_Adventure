#include "Pch.h"
#include "OverworldScene.h"


OverworldScene::OverworldScene(SharedContext aContext)
	: Scene{ aContext }
{
}

OverworldScene::~OverworldScene()
{
}

void OverworldScene::Update(float aDeltaTime)
{
}

void OverworldScene::LateUpdate(float aDeltaTime)
{
}

void OverworldScene::Draw() const
{
	// m_mapSystem.Draw();
}

#include "Core/Resources/ResourceHolder.hpp"
#include "../AI/BehaviorTree/Composite/CompositeNodes.h"
#include "../AI/BehaviorTree/Action/ActionNodes.h"
#include "../AI/BehaviorTree/Condition/ConditionNodes.h"

#include "Entity.h"
#include "Core/CoreComponents.h"
#include "Rendering/RenderComponents.h"
#include "Core/CoreComponents.h"
#include "Physics/PhysicsComponents.h"
#include "Rendering/RenderComponents.h"
#include "Controllers/ControllerComponents.h"
#include <Core/Resources/ResourceHolder.hpp>
#include "Combat/CombatComponents.h"


void OverworldScene::OnCreated()
{
}

void OverworldScene::OnEnter()
{


	auto& systemManager = m_sharedContext.m_systemManager;
	systemManager.Init(&m_entityManager);


	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");


	// m_mapSystem.Init(&m_entityManager);

	// Player
	auto player = m_entityManager.CreateResources("Player");
	//CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.42f, (float)Random::InRange(2, 62) };
	CU::Vector3<float> position = { 27.f, 0.42f, 25.f };
	player->GetComponent<TransformComponent>()->m_currentPos = position;

	auto time = m_entityManager.CreateResources("WorldTime");


	for (int i = 0; i < 10; ++i)
	{
		float x = 0.1 * i;
		auto* fish = m_entityManager.CreateResources("Fish");
		fish->GetComponent<TransformComponent>()->m_currentPos = { 10.f + x, 0.42f, 12.f };
	}


	auto crab = m_entityManager.CreateResources("Crab");
	crab->GetComponent<TransformComponent>()->m_currentPos = { 30.f, 0.42f, 30.f };

	auto raft = m_entityManager.CreateResources("Raft");
	raft->GetComponent<TransformComponent>()->m_currentPos = { 10.f, 0.42f, 10.f };

	auto hut = m_entityManager.CreateResources("Hut");
	hut->GetComponent<TransformComponent>()->m_currentPos = { 20.f, 0.85f, 30.f };

	auto npc = m_entityManager.CreateResources("Castaway");
	npc->GetComponent<TransformComponent>()->m_currentPos = { 15.f, 0.42f, 30.f };

	// Camera
	auto camera = m_entityManager.CreateResources("Camera");
	camera->GetComponent<TransformComponent>()->m_currentPos = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->m_targetOffset = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->m_targetID = (* m_entityManager.FindAllWithComponents<PlayerControllerComponent>().begin())->GetID();
	//camera->GetComponent<CameraComponent>()->m_target = *m_entityManager.FindAllWithComponents<PlayerControllerComponent>().begin();

	PostMaster::GetInstance().SendMessage({ eMessage::GameStarted, true }); 	// FIX
}

void OverworldScene::OnExit()
{
}
