#include "Pch.h"
#include "MapRenderSystem.h"
#include "EntityManager.h"
#include "Map/MapComponents.h"


MapRenderSystem::MapRenderSystem()
{
}

MapRenderSystem::~MapRenderSystem()
{
}

void MapRenderSystem::Receive(Message& aMsg)
{
}

void MapRenderSystem::Draw()
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAllWithComponents<MapChunkComponent>();

	// Todo; only render relevant map chunks (those in view)

	for (auto entity : entities)
	{
		auto* mapChunk = entity->GetComponent<MapChunkComponent>();
		auto currentPosition = entity->GetComponent<TransformComponent>()->m_currentPos;

		DrawMapChunk(mapChunk, currentPosition);
	}
}

void MapRenderSystem::DrawMapChunk(MapChunkComponent* aMapChunk, const CU::Vector3<float>& aPosition)
{
	static const float size = 1.f; // TODO; FIX!!

	for (const auto& tile : aMapChunk->m_tiles)
	{
		glm::vec3 position = { aPosition.x, aPosition.y, aPosition.z };
		position.x += tile.m_coordinates.x * size;
		position.z += tile.m_coordinates.y * size;
		
		// auto position = tile.m_position;
		Hi_Engine::BillboardRenderer::GetInstance().Render({ &tile.m_material, { position.x, position.y, position.z } , glm::vec3{1.f, 1.f, 1.f}, -90.f});
	}
}