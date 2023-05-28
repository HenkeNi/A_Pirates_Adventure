#include "Pch.h"
#include "Map.h"



#include "Core/Resources/ResourceHolder.hpp"

Map::Map()
	: m_mapWidth{ 64 }, m_mapHeight{ 64 }, m_tileSize{ 32 }, m_texture{ nullptr }
{
}

void Map::Init()
{
	//m_texture = &Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("overworld");
	m_texture = &Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("sand01");
	m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard"); // Change to sprite shader...	

	 

	m_materials.insert({ 1, Hi_Engine::Material{ m_texture, m_shader } });
	m_materials.insert({ 2, Hi_Engine::Material{ &Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("sea"), m_shader } });


	// 0 => 63
	//m_seaTiles.push_back()

}

void Map::Draw() const
{
	CU::Vector2<float> tileCoord;

	float tileWidth = 1.f;
	//float tileWidth = 1400 / m_mapWidth;
	float tileHeight = 1.f;
	//float tileHeight = 800 / m_mapHeight;

	//float offset = -0.1f;
	

	// Draw map
	for (int z = 0; z < m_mapHeight; ++z)
	{
		for (int x = 0; x < m_mapWidth; ++x)
		{/*
			tileCoord.x = x  * m_tileSize;
			tileCoord.y = y * m_tileSize;

			tileCoord.x /= 1400;
			tileCoord.y /= 800;*/

			




			//glm::vec3 position = { (tileWidth + 0.26f) * x + offset, (tileWidth + 0.26f) * z + offset, 0.f + tileHeight };	
			glm::vec3 position = { (tileWidth) * x, -0.1f, (tileWidth) * z };
			


			//CU::Vector3<float> position = { (tileWidth + 0.26f) * x + offset, 0.f, (tileWidth + 0.26f) * z + offset };


			//Hi_Engine::BillboardRenderer::GetInstance().Render({ {} , {pos.x, pos.y, pos.z}, {scale.x, scale.y}, m_transform->GetRotation()});

			
			glm::vec3					Position; // CU::Vector3<float>
			glm::vec2					Scale;			// Rename Scale or Size?? CU::Vector2<float>
			float						Rotation;



			if (z == 0 || z == m_mapHeight - 1 ||
				x == 0 || x == m_mapWidth - 1)
			{
				Hi_Engine::BillboardRenderer::GetInstance().Render({ &m_materials.at(2), position, m_tilePrototype.m_scale, m_tilePrototype.m_rotation});
			}
			else
				Hi_Engine::BillboardRenderer::GetInstance().Render({ &m_materials.at(1), position, m_tilePrototype.m_scale, m_tilePrototype.m_rotation});

			// Draw tile..
			//Hi_Engine::SpriteRenderer::GetInstance().Render({ &m_materials.at(1), position, m_tilePrototype.m_scale, m_tilePrototype.m_rotation});
			//Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_texture, m_tilePrototype.m_color, { (float)tileCoord.x + m_tileSize, (float)tileCoord.y, -1.f }, m_tilePrototype.m_scale, m_tilePrototype.m_rotation });
			
			
			
			// Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_texture, m_tilePrototype.m_color, position,  { tileWidth, tileHeight, 0.1f }, m_tilePrototype.m_rotation });
		
		}
	}

}
