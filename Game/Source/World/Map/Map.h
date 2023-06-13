#pragma once
#include "MapChunk.h"

// Look at instancing...

class MapRenderSystem;

// TileMap??
class Map
{
public:
	Map();

	void GenerateMap();

private:
	friend class MapRenderSystem;

	std::vector<MapChunk> m_chunks;








	struct Tile
	{
		CU::Vector4<float> m_color = { 1.f, 1.f, 1.f, 1.f };
		glm::vec2	m_scale = { 1.f, 1.f };
		//float				m_rotation = -90;
		//float				m_rotation = -88;
		//float				m_rotation = -70;
		unsigned			m_textureID;
	} m_tilePrototype;

	// tiles... -> opengl instancing..??

	// vector of ints? tile types... 


	unsigned m_mapWidth, m_mapHeight;	
	unsigned m_tileSize;

	// Texture...
	Hi_Engine::Texture2D* m_texture;
	Hi_Engine::Shader* m_shader;

	std::unordered_map<unsigned, Hi_Engine::Texture2D> m_textureMap;
	std::unordered_map<unsigned, Hi_Engine::Material> m_materials;


	std::vector<CU::Vector2<float>> m_seaTiles;
};

