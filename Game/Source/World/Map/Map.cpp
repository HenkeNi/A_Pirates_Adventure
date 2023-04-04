#include "Pch.h"
#include "Map.h"



#include "Core/Resources/ResourceHolder.hpp"

Map::Map()
	: m_mapWidth{ 16 }, m_mapHeight{ 16 }, m_tileSize{ 32 }, m_texture{ nullptr }
{
}

void Map::Init()
{
	m_texture = &Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("floor");
}

void Map::Draw() const
{
	CU::Vector2<unsigned> tileCoord;

	// Draw map
	for (int height = 0; height < m_mapHeight; ++height)
	{
		for (int width = 0; width < m_mapWidth; ++width)
		{
			tileCoord.x = width  * m_tileSize;
			tileCoord.y = height * m_tileSize;

			tileCoord.x /= 1400;
			tileCoord.y /= 800;


			// Draw tile..
			Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_texture, m_tilePrototype.m_color, {1 , 1, -1.f }, m_tilePrototype.m_scale, m_tilePrototype.m_rotation });
			Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_texture, m_tilePrototype.m_color, { (float)tileCoord.x + m_tileSize, (float)tileCoord.y, -1.f }, m_tilePrototype.m_scale, m_tilePrototype.m_rotation });
		
			return;
		}
	}

}
