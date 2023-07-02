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


void OverworldScene::OnCreated()
{
}

void OverworldScene::OnEnter()
{
	auto& systemManager = m_sharedContext.m_systemManager;
	systemManager.Init(&m_entityManager);


	m_map.GenerateMap();
	m_entityManager.LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");

	// Player
	auto player = m_entityManager.Create("Player");
	CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.3f, (float)Random::InRange(2, 62) };
	player->GetComponent<TransformComponent>()->m_currentPos = position;
	auto sprite = player->GetComponent<SpriteComponent>();
	sprite->m_material = {
		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("pirate_idle"),
		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };


	// Palm
	auto palm = m_entityManager.Create("PalmTree");
	palm->AddComponent(new TransformComponent);
	palm->AddComponent(new SpriteComponent);
	palm->GetComponent<TransformComponent>()->m_currentPos = position;
	auto treesprite = palm->GetComponent<SpriteComponent>();
	treesprite->m_material = {
		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("palm_01"),
		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };


	// Camera
	auto camera = m_entityManager.Create("Camera");
	camera->GetComponent<TransformComponent>()->m_currentPos = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->m_targetOffset = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->m_target = *m_entityManager.FindAllWithComponents<TransformComponent>().begin();


	// Grass




	/*Entity player;
	player.AddComponent(new TransformComponent);
	player.AddComponent(new SpriteComponent);
	player.AddComponent(new InputComponent);
	player.AddComponent(new PlayerControllerComponent);
	player.AddComponent(new VelocityComponent);

	CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.3f, (float)Random::InRange(2, 62) };

	player.GetComponent<TransformComponent>()->m_currentPos = position;
	auto sprite = player.GetComponent<SpriteComponent>();
	sprite->m_material = {
		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("pirate_idle"),
		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };
	m_entityManager.Add(std::move(player));*/
}

void OverworldScene::OnExit()
{
}
