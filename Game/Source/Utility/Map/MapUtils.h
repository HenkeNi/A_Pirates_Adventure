#pragma once

class Entity;
struct Tile;

namespace CU = CommonUtilities;

// Instead have a MapChunk class; MapChunkComponent store it as member..
class MapUtils
{
public:
	static Entity*	GetMapChunkAtPosition(const std::vector<Entity*>& someMapChunks, const CU::Vector2<float>& aPosition);

	static Tile*	GetTileAtWorldPosition(Entity* aMapChunk, const CU::Vector2<float>& aWorldPosition);

};