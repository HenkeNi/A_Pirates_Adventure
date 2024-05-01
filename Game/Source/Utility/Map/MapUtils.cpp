#include "Pch.h"
#include "MapUtils.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Map/MapComponents.h"
#include "Constants.h"
//#include "../../Data/Structs.h"


Entity* MapUtils::GetMapChunkAtPosition(const std::vector<Entity*>& mapChunks, const FVector2& position)
{
	for (const auto& mapChunk : mapChunks)
	{
		auto transformComponent = mapChunk->GetComponent<TransformComponent>();
		auto mapChunkComponent  = mapChunk->GetComponent<MapChunkComponent>();

		auto minXPosition = transformComponent->CurrentPos.x;
		auto minYPosition = transformComponent->CurrentPos.y;

		auto maxXPosition = minXPosition + Constants::MapChunkSize;
		//auto maxXPosition = minXPosition + mapChunkComponent->Width;
		auto maxYPosition = minYPosition + Constants::MapChunkSize;
		//auto maxYPosition = minYPosition + mapChunkComponent->Height;

		if (position.x < minXPosition || position.x > maxXPosition ||
			position.y < minYPosition || position.y > maxYPosition)
			continue;


		return mapChunk;
	}

	return nullptr;
}

Tile* MapUtils::GetTileAtWorldPosition(Entity* mapChunk, const FVector2& worldPosition)
{
	static float tileSize = 1.f;

	auto mapChunkTransform = mapChunk->GetComponent<TransformComponent>();
	auto mapChunkComponent = mapChunk->GetComponent<MapChunkComponent>();

	// calculate local position
	const FVector2 localPosition = worldPosition - FVector2{ mapChunkTransform->CurrentPos.x, mapChunkTransform->CurrentPos.y };

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

void MapUtils::GetCoordinates(int index, int width, int& outX, int& outY)
{
	outX = index % width;
	outY = index / width;
}

eTile MapUtils::GetTileTypeInDirection(const Entity* mapChunk, int index, eDirection direction)
{
	auto* mapChunkComponent = mapChunk->GetComponent<MapChunkComponent>();

	auto tiles = mapChunkComponent->Tiles;

	unsigned chunkSize = Constants::MapChunkLength;

	int row = index / chunkSize;
	int col = index % chunkSize;

	//if (aDirection == eDirection::Up && row > 0)
	if (direction == eDirection::Up && row < chunkSize - 1)
	{
		//int index = ((row - 1) * chunkSize) + col;
		int i = ((row + 1) * chunkSize) + col;
		return tiles.at(i).Type;
	}
	//if (aDirection == eDirection::Down && row < chunkSize - 1)
	if (direction == eDirection::Down && row > 0)
	{
		//int index = ((row + 1) * chunkSize) + col;
		int i = ((row - 1) * chunkSize) + col;
		return tiles.at(i).Type;
	}
	if (direction == eDirection::Left && col > 0)
	{
		int i = index - 1;
		return tiles.at(i).Type;
	}
	if (direction == eDirection::Right && col < chunkSize - 1)
	{
		int i = index + 1;
		return tiles.at(i).Type;
	}

	return eTile::Void;
}

int MapUtils::IsTileTypeInDirection(Entity* mapChunk, int index, eDirectionalValue direction, eTile type)
{
	auto* mapChunkComponent = mapChunk->GetComponent<MapChunkComponent>();

	auto tiles = mapChunkComponent->Tiles;

	unsigned chunkSize = Constants::MapChunkLength;

	int row = index / chunkSize;
	int col = index % chunkSize;

	//if (aDirection == eDirection::Up && row > 0)
	if (direction == eDirectionalValue::North && row < chunkSize - 1)
	{
		//int index = ((row - 1) * chunkSize) + col;
		int i = ((row + 1) * chunkSize) + col;
		return (tiles.at(i).Type == type);
	}
	//if (aDirection == eDirection::Down && row < chunkSize - 1)
	if (direction == eDirectionalValue::South && row > 0)
	{
		//int index = ((row + 1) * chunkSize) + col;
		int i = ((row - 1) * chunkSize) + col;
		return tiles.at(i).Type == type;
	}
	if (direction == eDirectionalValue::West && col > 0)
	{
		int i = index - 1;
		return tiles.at(i).Type == type;
	}
	if (direction == eDirectionalValue::East && col < chunkSize - 1)
	{
		int i = index + 1;
		return tiles.at(i).Type == type;
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