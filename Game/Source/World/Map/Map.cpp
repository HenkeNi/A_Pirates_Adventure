#include "Pch.h"
#include "Map.h"



#include "Core/Resources/ResourceHolder.hpp"

Map::Map()
	: m_mapWidth{ 64 }, m_mapHeight{ 64 }, m_tileSize{ 32 }, m_texture{ nullptr }
{
}

void Map::Init()
{
	m_texture = &Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("overworld");
	//m_texture = &Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("floor");
}

void Map::Draw() const
{
	CU::Vector2<float> tileCoord;

	float tileWidth = 0.75f;
	//float tileWidth = 1400 / m_mapWidth;
	float tileHeight = 0.75f;
	//float tileHeight = 800 / m_mapHeight;

	float offset = -1.5f;

	// Draw map
	for (int z = 0; z < m_mapHeight; ++z)
	{
		for (int x = 0; x < m_mapWidth; ++x)
		{/*
			tileCoord.x = x  * m_tileSize;
			tileCoord.y = y * m_tileSize;

			tileCoord.x /= 1400;
			tileCoord.y /= 800;*/



			CU::Vector3<float> position = { (tileWidth + 0.26f) * x + offset, (tileWidth + 0.26f) * z + offset, 0.f + tileHeight };
			//CU::Vector3<float> position = { (tileWidth + 0.26f) * x + offset, 0.f, (tileWidth + 0.26f) * z + offset };



			// Draw tile..
			//Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_texture, m_tilePrototype.m_color, {1 , 1, -1.f }, m_tilePrototype.m_scale, m_tilePrototype.m_rotation });
			//Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_texture, m_tilePrototype.m_color, { (float)tileCoord.x + m_tileSize, (float)tileCoord.y, -1.f }, m_tilePrototype.m_scale, m_tilePrototype.m_rotation });
			
			
			
			// Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_texture, m_tilePrototype.m_color, position,  { tileWidth, tileHeight, 0.1f }, m_tilePrototype.m_rotation });
		
		}
	}

}
