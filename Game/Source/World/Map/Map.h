#pragma once

// Look at instancing...

// TileMap??
class Map
{
public:
	Map();

	void Init();
	void Draw() const;

private:
	struct Tile
	{
		CU::Vector4<float> m_color = { 1.f, 1.f, 1.f, 1.f };
		CU::Vector2<float>	m_scale = { 1.f, 1.f };
		float				m_rotation = -90;
		//float				m_rotation = -70;
	} m_tilePrototype;

	// tiles... -> opengl instancing..??

	// vector of ints? tile types... 


	unsigned m_mapWidth, m_mapHeight;	
	unsigned m_tileSize;

	// Texture...
	Hi_Engine::Texture2D* m_texture;
};

