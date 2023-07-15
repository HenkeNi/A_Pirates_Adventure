#pragma once
#include "../Base/ComponentBase.h"


struct SpriteComponent : public ComponentBase
{
	Hi_Engine::Material m_material;
};

struct AnimationComponent : public ComponentBase
{
	float		m_frameDuration; // or total duration?
	unsigned	m_numOfFrames; // Frame amount
	unsigned	m_currentFrame;
	bool		m_isPlaying;
	bool		m_isLooping;
};

struct CameraComponent : public ComponentBase
{
	Hi_Engine::Camera	m_camera;
	CU::Vector3<float>  m_targetOffset;
	//class Entity*		m_target = nullptr;
	unsigned			m_targetID = 0;
};

struct RectComponent : public ComponentBase
{
	Hi_Engine::Shader* m_shader;
	CU::Vector4<float> m_color;
};


// SpriteSheet component? (stores texture atlas, also holds current frame, etc...)




// Shadow component??




// REMOVE!!!
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