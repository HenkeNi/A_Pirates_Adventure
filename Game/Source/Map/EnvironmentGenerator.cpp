#include "Pch.h"
#include "EnvironmentGenerator.h"
#include "../Entities/EntityManager.h"
#include "Core/CoreComponents.h"
#include "Rendering/RenderComponents.h"
#include <Core/Resources/ResourceHolder.hpp>
#include "Combat/CombatComponents.h"
#include "MapChunk.h"


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

	auto start = aChunk.GetStartPosition();
	auto end = aChunk.GetEndPosition();

//	auto width = aChunk. GetMinMaxWidth();  
	//auto height = aChunk.GetMinMaxHeight();

	GenerateFoilage("PalmTree", 2, start, end); // TODO; fix position
	GenerateFoilage("Grass", 7, start, end);

	static int count = 0;

	if ((count++) % 5 == 0)
		GenerateFoilage("SkeletonSpawner", 1, start, end);
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