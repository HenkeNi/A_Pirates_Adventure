#include "Pch.h"
#include "Map.h"

#include "Core/Resources/ResourceHolder.hpp"
#include "../PostMaster/PostMaster.h"
#include "../PostMaster/Message.h"


Map::Map()
	// : m_mapWidth{ 64 }, m_mapHeight{ 64 }, m_tileSize{ 32 }, m_texture{ nullptr }
{
}

void Map::GenerateMap()
{
	unsigned tileSize = 1.f;

	for (int col = 0; col < 5; ++col)
	{
		for (int row = 0; row < 5; ++row)
		{
			MapChunk chunk{};
			//chunk.SetPosition({ (float)col + chunk.m_chunkWidth * tileSize, 0.f, (float)row + chunk.m_chunkHeight * tileSize });
			chunk.SetPosition({ (float)col * (chunk.m_chunkWidth * tileSize),  0.f, (float)row * (chunk.m_chunkHeight * tileSize) });

			chunk.CreateTiles();
			
			m_chunks.push_back(chunk);
		}
	}




	PostMaster::GetInstance().SendMessage(Message{ eMessage::MapCreated, this }); // Send event?
}

void Map::Update()
{

}

void Map::Draw() const
{
	for (auto& chunk : m_chunks)
	{
		const auto& chunkPosition = chunk.m_position;

		const auto& tiles = chunk.m_tiles;

		for (const auto& tile : tiles)
		{
			glm::vec3 position = { chunkPosition.x, chunkPosition.y, chunkPosition.z };
			position.x += tile.m_chunkCoordinates.x * tile.m_size;
			position.z += tile.m_chunkCoordinates.y * tile.m_size;


			Hi_Engine::BillboardRenderer::GetInstance().Render({ &tile.m_material, position, glm::vec3{ 1.f, 1.f, 1.f}, -90.f });
		}
	}
}

//void Map::Init()
//{
//	//m_texture = &Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("overworld");
//	//m_texture = &Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("sand01");
//	m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard"); // Change to sprite shader...		 
//
//	m_materials.insert({ 1, Hi_Engine::Material{ m_texture, m_shader } });
//	m_materials.insert({ 2, Hi_Engine::Material{ &Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("sea"), m_shader } });
//	m_materials.insert({ 3, Hi_Engine::Material{ &Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("grass_tile"), m_shader } });
//
//}

//void Map::Draw() const
//{
//	CU::Vector2<float> tileCoord;
//
//	float tileWidth = 1.f;
//	//float tileWidth = 1400 / m_mapWidth;
//	float tileHeight = 1.f;
//	//float tileHeight = 800 / m_mapHeight;
//
//	//float offset = -0.1f;
//	
//
//	// Draw map
//	for (int z = 0; z < m_mapHeight; ++z)
//	{
//		for (int x = 0; x < m_mapWidth; ++x)
//		{/*
//			tileCoord.x = x  * m_tileSize;
//			tileCoord.y = y * m_tileSize;
//
//			tileCoord.x /= 1400;
//			tileCoord.y /= 800;*/
//
//			
//
//
//
//
//			//glm::vec3 position = { (tileWidth + 0.26f) * x + offset, (tileWidth + 0.26f) * z + offset, 0.f + tileHeight };	
//			glm::vec3 position = { (tileWidth) * x, -0.1f, (tileWidth) * z };
//			
//
//
//			//CU::Vector3<float> position = { (tileWidth + 0.26f) * x + offset, 0.f, (tileWidth + 0.26f) * z + offset };
//
//
//			//Hi_Engine::BillboardRenderer::GetInstance().Render({ {} , {pos.x, pos.y, pos.z}, {scale.x, scale.y}, m_transform->GetRotation()});
//
//			
//			glm::vec3					Position; // CU::Vector3<float>
//			glm::vec2					Scale;			// Rename Scale or Size?? CU::Vector2<float>
//			float						Rotation;
//
//
//
//			if (z == 0 || z == m_mapHeight - 1 ||
//				x == 0 || x == m_mapWidth - 1)
//			{
//				Hi_Engine::BillboardRenderer::GetInstance().Render({ &m_materials.at(2), position, m_tilePrototype.m_scale, m_tilePrototype.m_rotation});
//			}
//			else if (z > (m_mapHeight * 0.45f) && z < (m_mapHeight * 0.65f) && x >(m_mapWidth * 0.35f) && x < (m_mapWidth * 0.75f))
//				Hi_Engine::BillboardRenderer::GetInstance().Render({ &m_materials.at(3), position, m_tilePrototype.m_scale, m_tilePrototype.m_rotation});
//			else
//				Hi_Engine::BillboardRenderer::GetInstance().Render({ &m_materials.at(1), position, m_tilePrototype.m_scale, m_tilePrototype.m_rotation});
//
//			// Draw tile..
//			//Hi_Engine::SpriteRenderer::GetInstance().Render({ &m_materials.at(1), position, m_tilePrototype.m_scale, m_tilePrototype.m_rotation});
//			//Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_texture, m_tilePrototype.m_color, { (float)tileCoord.x + m_tileSize, (float)tileCoord.y, -1.f }, m_tilePrototype.m_scale, m_tilePrototype.m_rotation });
//			
//			
//			
//			// Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_texture, m_tilePrototype.m_color, position,  { tileWidth, tileHeight, 0.1f }, m_tilePrototype.m_rotation });
//		
//		}
//	}
//
//}
