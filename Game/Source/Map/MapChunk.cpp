#include "Pch.h"
#include "MapChunk.h"
#include <Core/Resources/ResourceHolder.hpp>


MapChunk::MapChunk(const CU::Vector3<float>& aStartPosition)
	: m_chunkWidth{ 10 }, m_chunkHeight{ 10 }, m_position{ aStartPosition }
{
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
