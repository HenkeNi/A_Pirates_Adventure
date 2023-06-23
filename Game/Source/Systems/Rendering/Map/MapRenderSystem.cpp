#include "Pch.h"
#include "MapRenderSystem.h"
#include "../World/Map/Map.h"
#include "../World/Map/MapChunk.h"


#include "../PostMaster/Subscriber.h"
#include "../PostMaster/PostMaster.h"
#include "../PostMaster/Message.h"

MapRenderSystem::MapRenderSystem()
	: System{ 0 }, m_map{ nullptr }
{
	PostMaster::GetInstance().Subscribe(eMessage::MapCreated, this);
}

MapRenderSystem::~MapRenderSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::MapCreated, this);
}

void MapRenderSystem::Receive(Message& aMsg)
{
	// Pass level/map by event?

	if (aMsg.GetMessageType() == eMessage::MapCreated)
		m_map = std::any_cast<Map*>(aMsg.GetData());
}

void MapRenderSystem::Draw()
{
	if (!m_map)
		return;

	// TODO; Check player position (render relevant chunks)
	for (const auto& chunk : m_map->m_chunks)
	{
		RenderChunk(chunk);
	}
}

void MapRenderSystem::RenderChunk(const MapChunk& aMapChunk)
{
	/*const auto& chunkPosition = aMapChunk.m_position;

	const auto& tiles = aMapChunk.m_tiles;

	for (const auto& tile : tiles)
	{
		glm::vec3 position = { chunkPosition.x, chunkPosition.y, chunkPosition.z };
		position.x += tile.m_chunkCoordinates.x * tile.m_size;
		position.z += tile.m_chunkCoordinates.y * tile.m_size;


		Hi_Engine::BillboardRenderer::GetInstance().Render({ &tile.m_material, position, glm::vec3{ 1.f, 1.f, 1.f}, -90.f });
	}*/
}