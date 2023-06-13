#pragma once
#include "../ComponentBase.h"


struct SpriteComponent : public ComponentBase
{
	Hi_Engine::Material m_material;
};


struct CameraComponent : public ComponentBase
{
	Hi_Engine::Camera	m_camera;
	class Entity*		m_target = nullptr;
	CU::Vector3<float>  m_targetOffset;
};


// Animation component? 



struct TileComponent : public ComponentBase
{
	// Tile specific data..
	CU::Vector2<float>	m_size;
	unsigned			m_type;		
	bool				m_isTraversable; // Needed???
};

struct MapChunkComponent : public ComponentBase
{
	CU::Vector2<unsigned>	m_size;
	CU::Vector2<int>		m_position;
	unsigned				m_chunkID;


	// Data for chunk of tiles
 };

// Store each tile as an Entity? depending on which chunk it is in => render it or not..???