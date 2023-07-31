#pragma once

class Entity;
struct Tile;

// Instead have a MapChunk class; MapChunkComponent store it as member..
class MapUtils
{
public:
	static Entity*	GetMapChunkAtPosition(const std::vector<Entity*>& someMapChunks, const CU::Vector2<float>& aPosition);

	static Tile*	GetTileAtPosition(const std::vector<Entity*>& someMapChunks, const CU::Vector2<float>& aPosition);


};