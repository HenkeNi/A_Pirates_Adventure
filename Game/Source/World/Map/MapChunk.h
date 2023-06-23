#pragma once
#include "Tile.h"

//class MapRenderSystem;

class MapChunk
{
public:
	MapChunk();
	~MapChunk();


	void CreateTiles();

	


private:



	CU::Vector3<float>	m_position;	// rename worldPosiiton??	Upper left corner??
	std::vector<Tile>	m_tiles;
	unsigned			m_chunkWidth, m_chunkHeight;	// Combine??
};

