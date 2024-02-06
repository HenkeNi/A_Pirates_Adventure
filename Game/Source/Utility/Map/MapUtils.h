#pragma once

class Entity;
struct Tile;

namespace CU = CommonUtilities;

// Instead have a MapChunk class; MapChunkComponent store it as member..
class MapUtils // Static functions in one of the MapSystems?
{
public:
	static Entity*	GetMapChunkAtPosition(const std::vector<Entity*>& someMapChunks, const CU::Vector2<float>& aPosition);

	static Tile*	GetTileAtWorldPosition(Entity* aMapChunk, const CU::Vector2<float>& aWorldPosition);

	static void		GetCoordinates(int aIndex, int aWidth, int& outX, int& outY);
};