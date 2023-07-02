#pragma once
#include "Tile.h"

//class MapRenderSystem;
class Map;

class MapChunk
{
public:
	MapChunk(const CU::Vector3<float>& aStartPosition = { 0.f, 0.f, 0.f });
	~MapChunk();


	void CreateTiles();

	void SetPosition(const CU::Vector3<float>& aStartPosition);


private:
	friend class Map;


	CU::Vector3<float>	m_position;	// rename worldPosiiton??	Upper left corner??
	std::vector<Tile>	m_tiles;
	unsigned			m_chunkWidth, m_chunkHeight;	// Combine??	rename ChunkTileAmount??
};