#include "Pch.h"
#include "MapChunk.h"
#include <Core/Resources/ResourceHolder.hpp>


MapChunk::MapChunk()
	: m_chunkWidth{ 10 }, m_chunkHeight{ 10 }, m_position{ 0.f, 0.f, 0.f }
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
		}
	}


}