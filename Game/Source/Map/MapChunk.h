#pragma once
#include "Tile.h"

//class MapRenderSystem;
class MapSystem;
class Map;
class MapGenerator;

class MapChunk
{
public:
	MapChunk(const CU::Vector3<float>& aStartPosition = { 0.f, 0.f, 0.f });
	~MapChunk();


	void CreateTiles();
	void CreateTiles(bool isLand);

	void SetPosition(const CU::Vector3<float>& aStartPosition);

	CU::Vector2<float> GetStartPosition()	const;
	CU::Vector2<float> GetEndPosition()		const;

	/*CU::Vector2<float> GetMinMaxWidth()		const;
	CU::Vector2<float> GetMinMaxHeight()	const;*/

	static float GetSize();

	inline bool IsWater() const // FIX!
	{
		return m_isWater;
	}

private:
	friend class MapSystem;
	friend class Map;
	friend class MapGenerator;

	static unsigned		s_widthInTiles;

	bool m_isWater = false; // FIX!

	CU::Vector3<float>	m_position;	// rename worldPosiiton??	Upper left corner??
	std::vector<Tile>	m_tiles;
	unsigned			m_chunkWidth, m_chunkHeight;	// Combine??	rename ChunkTileAmount??
};