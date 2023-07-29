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
#include "../AI/BehaviorTree/SelectorNode.h"
#include "../AI/BehaviorTree/SequenceNode.h"
#include "../AI/BehaviorTree/ActionNodes.h"
#include "../AI/BehaviorTree/ConditionNodes.h"

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
	auto player = m_entityManager.Create("Player");
	CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.42f, (float)Random::InRange(2, 62) };
	player->GetComponent<TransformComponent>()->m_currentPos = position;


	// Camera
	auto camera = m_entityManager.Create("Camera");
	camera->GetComponent<TransformComponent>()->m_currentPos = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->m_targetOffset = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->m_targetID = (* m_entityManager.FindAllWithComponents<PlayerControllerComponent>().begin())->GetID();
	//camera->GetComponent<CameraComponent>()->m_target = *m_entityManager.FindAllWithComponents<PlayerControllerComponent>().begin();

	PostMaster::GetInstance().SendMessage({ eMessage::GameStarted, true }); 	// FIX
}

void OverworldScene::OnExit()
{
}
