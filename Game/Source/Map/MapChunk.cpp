#include "Pch.h"
#include "MapChunk.h"
#include <Core/Resources/ResourceHolder.hpp>


unsigned MapChunk::s_widthInTiles = 0;


MapChunk::MapChunk(const CU::Vector3<float>& aStartPosition)
	: m_chunkWidth{ 10 }, m_chunkHeight{ 10 }, m_position{ aStartPosition }
{
	s_widthInTiles = m_chunkWidth * 1.f; //Tile::m_size;
}

MapChunk::~MapChunk()
{
}

void MapChunk::CreateTiles()
{
	for (unsigned height = 0; height < m_chunkHeight; ++height)
	{
		for (unsigned width = 0; width < m_chunkWidth; ++width)
		{
			Tile tile;
			tile.m_chunkCoordinates = { height, width };
			Hi_Engine::Material material{
				&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("sand01"),
				&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard")
			};
			tile.m_material = material;

			m_tiles.push_back(tile);
		}
	}


}

void MapChunk::SetPosition(const CU::Vector3<float>& aStartPosition)
{
	m_position = aStartPosition;
}

CU::Vector2<float> MapChunk::GetStartPosition() const
{
	return { m_position.x, m_position.z };

	//return CU::Vector2<float>();
}

CU::Vector2<float> MapChunk::GetEndPosition() const
{
	static float tileSize = 1.f; // FIX!
	return { m_position.x + s_widthInTiles * tileSize, m_position.z + s_widthInTiles * tileSize };
}

float MapChunk::GetSize()
{
	return s_widthInTiles;
}

//CU::Vector2<float> MapChunk::GetMinMaxWidth() const
//{
//	return CU::Vector2<float>();
//}
//
//CU::Vector2<float> MapChunk::GetMinMaxHeight() const
//{
//	return CU::Vector2<float>();
//}
