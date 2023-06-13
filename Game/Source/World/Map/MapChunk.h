#pragma once

class MapRenderSystem;

class MapChunk
{
public:
	MapChunk();
	~MapChunk();


	void CreateTiles();

	struct Tile
	{
		// Texture and shader
		Hi_Engine::Material		m_material; // Pointer? -> shared..?

		CU::Vector4<float>		m_color = { 1.f, 1.f, 1.f, 1.f };
		//glm::vec2				m_size; // make static?
		float					m_size; // make static?
		unsigned				m_textureID;
		CU::Vector2<unsigned>	m_chunkCoordinates;

		// Type
	};

private:
	friend class MapRenderSystem;

	CU::Vector3<float>	m_position;	// rename worldPosiiton??	Upper left corner??
	std::vector<Tile>	m_tiles;
	unsigned			m_chunkWidth, m_chunkHeight;	// Combine??
};

