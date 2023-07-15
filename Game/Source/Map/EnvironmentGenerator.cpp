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


	GenerateFoilage("PalmTree", 2, { 2, 2 }, { 62, 62 });
	GenerateFoilage("Grass", 7, { 2, 2 }, { 62, 62 });
}


void EnvironmentGenerator::GenerateFoilage(const std::string& aType, unsigned anAmount, const CU::Vector2<float> someMinPositions, const CU::Vector2<float> someMaxPositions)	// Maybe pass in a position?
{
	for (int i = 0; i < anAmount; ++i)
	{
		auto* entity = m_entityManager->Create(aType);
		auto* transform = entity->GetComponent<TransformComponent>();

		CU::Vector2<float> position = { (float)Random::InRange(someMinPositions.x, someMaxPositions.x), (float)Random::InRange(someMinPositions.y, someMaxPositions.y) };
		
		transform->m_currentPos = transform->m_previousPos = { position.x, transform->m_currentPos.y, position.y };
		//transform->m_scale = { 0.75f, 0.75f, 0.75f };														// should be read from json...

		//auto rect = entity->GetComponent<RectComponent>();
		//rect->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Primitive");

		// Fix somehow => need to work even if not moving
		auto hitbox = entity->GetComponent<HitboxColliderComponent>();

		static float size = 0.2f;

		hitbox->m_collider.Init({ position.x - size, position.y - size }, { position.x + size, position.y + size });

	}
}