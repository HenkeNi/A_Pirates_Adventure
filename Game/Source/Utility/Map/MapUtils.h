#pragma once

class Entity;
struct Tile;

namespace CU = CommonUtilities;

// Instead have a MapChunk class; MapChunkComponent store it as member..
class MapUtils // Static functions in one of the MapSystems?
{
public:
	static Entity*	GetMapChunkAtPosition(const std::vector<Entity*>& mapChunks, const CU::Vector2<float>& position);

	static Tile*	GetTileAtWorldPosition(Entity* mapChunk, const CU::Vector2<float>& worldPosition);

	static void		GetCoordinates(int index, int width, int& outX, int& outY);

	static eTile GetTileTypeInDirection(const Entity* mapChunk, int index, eDirection direction);

	static int IsTileTypeInDirection(Entity* mapChunk, int index, eDirectionalValue direction, eTile type);
};