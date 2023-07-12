#include "Pch.h"
#include "EnvironmentGenerator.h"
#include "../Entities/EntityManager.h"
#include "Core/CoreComponents.h"
#include "Rendering/RenderComponents.h"
#include <Core/Resources/ResourceHolder.hpp>
#include "Combat/CombatComponents.h"



EnvironmentGenerator::EnvironmentGenerator()
	: m_entityManager{ nullptr }
{
}

EnvironmentGenerator::~EnvironmentGenerator()
{
}

void EnvironmentGenerator::Init(EntityManager* anEntityManager)
{
	m_entityManager = anEntityManager;
}

void EnvironmentGenerator::PopulateMapChunk(class MapChunk& aChunk)
{
	if (!m_entityManager)
		return;


	// Read chunk data (tile types, etc...)



	// Add some tress....
	for (int i = 0; i < 2; ++i)
	{
		CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.65f, (float)Random::InRange(2, 62) };

		auto palm = m_entityManager->Create("PalmTree");
		palm->GetComponent<TransformComponent>()->m_currentPos = position;
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
		hitbox->m_collider.Init({ position.x - palmSize, position.z - palmSize }, { position.x + palmSize, position.z + palmSize });
	}




	// some gras...
	for (int i = 0; i < 5; ++i)
	{
		auto* grass = m_entityManager->Create("Grass");
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
		auto* smallGrass = m_entityManager->Create("Grass");
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


}