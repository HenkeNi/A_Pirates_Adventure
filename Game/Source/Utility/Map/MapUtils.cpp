#include "Pch.h"
#include "MapUtils.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Map/MapComponents.h"
//#include "../../Data/Structs.h"


Entity* MapUtils::GetMapChunkAtPosition(const std::vector<Entity*>& someMapChunks, const CU::Vector2<float>& aPosition)
{
	for (const auto& mapChunk : someMapChunks)
	{
		auto transformComponent = mapChunk->GetComponent<TransformComponent>();
		auto mapChunkComponent  = mapChunk->GetComponent<MapChunkComponent>();

		auto minXPosition = transformComponent->CurrentPos.x;
		auto minYPosition = transformComponent->CurrentPos.y;

		auto maxXPosition = minXPosition + MapChunkComponent::TileCountPerSide;
		//auto maxXPosition = minXPosition + mapChunkComponent->Width;
		auto maxYPosition = minYPosition + MapChunkComponent::TileCountPerSide;
		//auto maxYPosition = minYPosition + mapChunkComponent->Height;

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
	const CU::Vector2<float> localPosition = aWorldPosition - CU::Vector2<float>{ mapChunkTransform->CurrentPos.x, mapChunkTransform->CurrentPos.y };

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

void MapUtils::GetCoordinates(int aIndex, int aWidth, int& outX, int& outY)
{
	outX = aIndex % aWidth;
	outY = aIndex / aWidth;
}

eTile MapUtils::GetTileTypeInDirection(const Entity* aMapChunk, int anIndex, eDirection aDirection)
{
	auto* mapChunkComponent = aMapChunk->GetComponent<MapChunkComponent>();

	auto tiles = mapChunkComponent->Tiles;

	unsigned chunkSize = MapChunkComponent::TileCountPerSide;

	int row = anIndex / chunkSize;
	int col = anIndex % chunkSize;

	//if (aDirection == eDirection::Up && row > 0)
	if (aDirection == eDirection::Up && row < chunkSize - 1)
	{
		//int index = ((row - 1) * chunkSize) + col;
		int index = ((row + 1) * chunkSize) + col;
		return tiles.at(index).Type;
	}
	//if (aDirection == eDirection::Down && row < chunkSize - 1)
	if (aDirection == eDirection::Down && row > 0)
	{
		//int index = ((row + 1) * chunkSize) + col;
		int index = ((row - 1) * chunkSize) + col;
		return tiles.at(index).Type;
	}
	if (aDirection == eDirection::Left && col > 0)
	{
		int index = anIndex - 1;
		return tiles.at(index).Type;
	}
	if (aDirection == eDirection::Right && col < chunkSize - 1)
	{
		int index = anIndex + 1;
		return tiles.at(index).Type;
	}

	return eTile::Void;
}

int MapUtils::IsTileTypeInDirection(Entity* aMapChunk, int anIndex, eDirectionalValue aDirection, eTile aType)
{
	auto* mapChunkComponent = aMapChunk->GetComponent<MapChunkComponent>();

	auto tiles = mapChunkComponent->Tiles;

	unsigned chunkSize = MapChunkComponent::TileCountPerSide;

	int row = anIndex / chunkSize;
	int col = anIndex % chunkSize;

	//if (aDirection == eDirection::Up && row > 0)
	if (aDirection == eDirectionalValue::North && row < chunkSize - 1)
	{
		//int index = ((row - 1) * chunkSize) + col;
		int index = ((row + 1) * chunkSize) + col;
		return (tiles.at(index).Type == aType);
	}
	//if (aDirection == eDirection::Down && row < chunkSize - 1)
	if (aDirection == eDirectionalValue::South && row > 0)
	{
		//int index = ((row + 1) * chunkSize) + col;
		int index = ((row - 1) * chunkSize) + col;
		return tiles.at(index).Type == aType;
	}
	if (aDirection == eDirectionalValue::West && col > 0)
	{
		int index = anIndex - 1;
		return tiles.at(index).Type == aType;
	}
	if (aDirection == eDirectionalValue::East && col < chunkSize - 1)
	{
		int index = anIndex + 1;
		return tiles.at(index).Type == aType;
	}

	return 0;
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