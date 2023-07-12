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
	m_mapSystem.Draw();
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

	m_entityManager.LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");

	m_mapSystem.Init(&m_entityManager);

	// Player
	auto player = m_entityManager.Create("Player");
	CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.42f, (float)Random::InRange(2, 62) };
	player->GetComponent<TransformComponent>()->m_currentPos = position;
	auto sprite = player->GetComponent<SpriteComponent>();
	sprite->m_material = {
		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("pirate_idle"),
		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };
	auto rect = player->GetComponent<RectComponent>();
	rect->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Primitive");
	auto attack = player->GetComponent<AttackColliderComponent>();
	attack->m_offset = { 1.f, 0.f, 0.f };

	auto colliderPos = position + attack->m_offset;
	auto size = 0.2f;

	attack->m_collider.Init({ colliderPos.x - size, colliderPos.z - size }, { colliderPos.x + size, colliderPos.z + size });
	//attack->m_collider.Init({ colliderPos.x - collider.GetWidth() * 0.5f, colliderPos.x + collider.GetWidth() * 0.5f }, { colliderPos.z - collider.GetHeight() * 0.5f, colliderPos.z + collider.GetHeight() * 0.5f });
	//attack->m_collider.Init({ position.x + attack->m_offset.x 2.f, position.x + attack->m_offset.x + 2.f }, { position.z + attack->m_offset.y - 2.f, position.z + attack->m_offset.y + 2.f });

	// Camera
	auto camera = m_entityManager.Create("Camera");
	camera->GetComponent<TransformComponent>()->m_currentPos = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->m_targetOffset = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->m_targetID = (* m_entityManager.FindAllWithComponents<PlayerControllerComponent>().begin())->GetID();
	//camera->GetComponent<CameraComponent>()->m_target = *m_entityManager.FindAllWithComponents<PlayerControllerComponent>().begin();
}

void OverworldScene::OnExit()
{
}
