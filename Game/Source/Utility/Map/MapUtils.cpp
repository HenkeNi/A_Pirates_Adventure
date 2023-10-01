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

		auto minXPosition = transformComponent->CurrentPos.x;
		auto minYPosition = transformComponent->CurrentPos.z;

		auto maxXPosition = minXPosition + mapChunkComponent->Width;
		auto maxYPosition = minYPosition + mapChunkComponent->Height;

		if (aPosition.x < minXPosition || aPosition.x > maxXPosition ||
			aPosition.y < minYPosition || aPosition.y > maxYPosition)
			continue;


		return mapChunk;
	}

	return nullptr;
}

Tile* MapUtils::GetTileAtWorldPosition(Entity* aMapChunk, const CU::Vector2<float>& aWorldPosition)
{
	static float tileSize = 1.f;

	auto mapChunkTransform = aMapChunk->GetComponent<TransformComponent>();
	auto mapChunkComponent = aMapChunk->GetComponent<MapChunkComponent>();

	// calculate local position
	const CU::Vector2<float> localPosition = aWorldPosition - CU::Vector2<float>{ mapChunkTransform->CurrentPos.x, mapChunkTransform->CurrentPos.z };

	//std::cout << "Locla: " << localPosition.x << ", " << localPosition.y << '\n';

	int tileRow = (int)localPosition.y / tileSize;
	int tileCol = (int)localPosition.x / tileSize;

	//std::cout << tileRow << ", col: " << tileCol << '\n';

	int tileIndex = tileRow * 10 + tileCol;

	// std::cout << "Index: " << tileIndex << '\n';

	return &mapChunkComponent->Tiles.at(tileIndex);

	//Tile* tile = nullptr;

	//for (auto& tile : mapChunkComponent->m_tiles)
	//{




	//	if (aPosition.x < tile.m_position.x || aPosition.y < tile.m_position.z || aPosition.x > (tile.m_position.x + tileSize) || aPosition.y > (tile.m_position.z + tileSize))
	//		continue;


	//	return &tile;
	//}



	//int width  = mapChunkComponent->m_width;
	//int height = mapChunkComponent->m_height;

	/*if (aPosition.x >= 0 && aXCoord < width && aPosition.y >= 0 && aYCoord < height)
	{
		return &mapChunkComponent->m_tiles[aPosition.y * width * aPosition.x];
	}*/

	return nullptr;
	//return tile;
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