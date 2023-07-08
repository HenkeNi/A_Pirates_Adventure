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
	m_map.Draw();
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


	m_map.GenerateMap();
	m_entityManager.LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");

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
	camera->GetComponent<CameraComponent>()->m_target = *m_entityManager.FindAllWithComponents<PlayerControllerComponent>().begin();


	// Trees
	for (int i = 0; i < 70; ++i)
	{
		auto palm = m_entityManager.Create("PalmTree");
		palm->AddComponent(new TransformComponent);
		palm->AddComponent(new SpriteComponent);

		CU::Vector3<float> palmPostition = { (float)Random::InRange(2, 62), 0.65f, (float)Random::InRange(2, 62) };
		palm->GetComponent<TransformComponent>()->m_currentPos = palmPostition;
		palm->GetComponent<TransformComponent>()->m_scale = { 1.f, 1.85f, 1.f };

		auto treesprite = palm->GetComponent<SpriteComponent>();
		treesprite->m_material = {
			&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("palm_01"),
			&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };


		// Collider...
		auto palmRect = palm->GetComponent<RectComponent>();
		palmRect->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Primitive");
		auto hitbox = palm->GetComponent<HitboxColliderComponent>();

		auto palmSize = 0.2f;

		hitbox->m_collider.Init({ palmPostition.x - palmSize, palmPostition.z - palmSize }, { palmPostition.x + palmSize, palmPostition.z + palmSize });
	}


	// Grass
	for (int i = 0; i < 115; ++i)
	{
		auto grass = m_entityManager.Create("Grass");
		grass->AddComponent(new TransformComponent);
		grass->AddComponent(new SpriteComponent);

		auto pos = CU::Vector3<float>{ (float)Random::InRange(2, 62), 0.3f, (float)Random::InRange(2, 62) };
		grass->GetComponent<TransformComponent>()->m_currentPos = pos;
		grass->GetComponent<TransformComponent>()->m_scale = { 0.75f, 0.75f, 0.75f };

		auto grassSprite = grass->GetComponent<SpriteComponent>();
		grassSprite->m_material = {
			&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("grass"),
			&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };

		// collider
		auto grassRect = grass->GetComponent<RectComponent>();
		grassRect->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Primitive");
		auto largehitbox = grass->GetComponent<HitboxColliderComponent>();

		auto grassSize = 0.2f;

		largehitbox->m_collider.Init({ pos.x - grassSize, pos.z - grassSize }, { pos.x + grassSize, pos.z + grassSize });


		// small grass
		auto smallGrass = m_entityManager.Create("Grass");
		smallGrass->AddComponent(new TransformComponent);
		smallGrass->AddComponent(new SpriteComponent);

		smallGrass->GetComponent<TransformComponent>()->m_currentPos = { pos.x, pos.y - 0.1f, pos.z + 0.1f };
		smallGrass->GetComponent<TransformComponent>()->m_scale = { 0.5f, 0.5f, 0.5f };

		auto smallGrassSprite = smallGrass->GetComponent<SpriteComponent>();
		smallGrassSprite->m_material = {
			&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("grass"),
			&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };



		auto smallgrassRect = smallGrass->GetComponent<RectComponent>();
		smallgrassRect->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Primitive");
		auto smallhitbox = smallGrass->GetComponent<HitboxColliderComponent>();

		CU::Vector3<float> p = { pos.x, pos.y - 0.1f, pos.z + 0.1f };
		smallhitbox->m_collider.Init({ p.x - grassSize, p.z - grassSize }, { p.x + grassSize, p.z + grassSize });

	}



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
