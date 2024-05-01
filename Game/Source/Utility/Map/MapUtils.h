#pragma once

class Entity;
struct Tile;

// Instead have a MapChunk class; MapChunkComponent store it as member..
class MapUtils // Static functions in one of the MapSystems?
{
public:
	static Entity*	GetMapChunkAtPosition(const std::vector<Entity*>& mapChunks, const FVector2& position);

	static Tile*	GetTileAtWorldPosition(Entity* mapChunk, const FVector2& worldPosition);

	static void		GetCoordinates(int index, int width, int& outX, int& outY); // maybe dont use in-out parameters?!

	static eTile GetTileTypeInDirection(const Entity* mapChunk, int index, eDirection direction);

	static int IsTileTypeInDirection(Entity* mapChunk, int index, eDirectionalValue direction, eTile type);
};