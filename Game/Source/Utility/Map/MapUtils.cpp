#include "Pch.h"
#include "MapUtils.h"
#include "Entity.h"
#include "Core/CoreComponents.h"
#include "Map/MapComponents.h"
#include "../../Data/Structs.h"


Entity* MapUtils::GetMapChunkAtPosition(const std::vector<Entity*>& someMapChunks, const CU::Vector2<float>& aPosition)
{
	for (const auto& mapChunk : someMapChunks)
	{
		auto transformComponent = mapChunk->GetComponent<TransformComponent>();
		auto mapChunkComponent  = mapChunk->GetComponent<MapChunkComponent>();

		auto minXPosition = transformComponent->m_currentPos.x;
		auto minYPosition = transformComponent->m_currentPos.z;

		auto maxXPosition = minXPosition + mapChunkComponent->m_width;
		auto maxYPosition = minYPosition + mapChunkComponent->m_height;

		if (aPosition.x < minXPosition || aPosition.x > maxXPosition ||
			aPosition.y < minYPosition || aPosition.y > maxYPosition)
			continue;


		return mapChunk;
	}

	return nullptr;
}

Tile* MapUtils::GetTileAtPosition(const std::vector<Entity*>& someMapChunks, const CU::Vector2<float>& aPosition)
{
	auto mapChunk = GetMapChunkAtPosition(someMapChunks, aPosition);

	auto mapChunkComponent = mapChunk->GetComponent<MapChunkComponent>();

	Tile* tile = nullptr;

	for (const auto& tile : mapChunkComponent->m_tiles)
	{
		// if (tile.m_position.x)

	}



	int width  = mapChunkComponent->m_width;
	int height = mapChunkComponent->m_height;

	/*if (aPosition.x >= 0 && aXCoord < width && aPosition.y >= 0 && aYCoord < height)
	{
		return &mapChunkComponent->m_tiles[aPosition.y * width * aPosition.x];
	}*/

	return tile;
}



//auto mapChunkComponent = aMapChunk->GetComponent<MapChunkComponent>();
//int width = mapChunkComponent->m_width;
//int height = mapChunkComponent->m_height;
//
//if (aXCoord >= 0 && aXCoord < width && aYCoord >= 0 && aYCoord < height)
//{
//	return &mapChunkComponent->m_tiles[aYCoord * width * aXCoord];
//}
//
//return nullptr;