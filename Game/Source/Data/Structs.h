#pragma once
#include "Enumerations.h"
#include "../Scenes/SceneManagerProxy.h"
#include <any>
//#include <Hi_Engine.h> // Fix
#include  <../../../Engine/Source/Utility/Math/Vectors/Vector.hpp>
#include  <../../../Engine/Source/Core/Rendering/Material/Material.h>
#include  <../../../Engine/Source/Core/Rendering/Texture/Subtexture2D.h>

namespace CU = CommonUtilities;

// Todo; change naming convention to sceneManager, rather thna m_sceneManager;

struct SharedContext
{
	SceneManagerProxy		m_sceneManager;
	class SystemManager&	m_systemManager;
};


struct CollisionData // Data used for resolving/handling collisions
{
	unsigned m_damageDealt = 0;
};

template <typename T>
struct Range
{
	T m_min;
	T m_max;
};


struct Tile
{
	//Hi_Engine::Material m_material;
	class Hi_Engine::Subtexture2D* m_subtexture;
	CU::Vector4<float> m_color  = { 1.f, 1.f, 1.f, 1.f }; // DO ELSEWHER!?
	CU::Vector3<float>	m_position;			// store chunk coordiante instead?
	CU::Vector2<int>	m_coordinates;			// Use only one!!
	eTile				m_type;
	bool				m_isCollidable;
};

// Put in Engine??
struct Animation
{
	std::vector<std::string>	m_sprites;
	unsigned					m_totalFrames;
	unsigned					m_currentFrame;
	float						m_frameDuration;
	float						m_elapsedFrameTime;
	bool						m_isPlaying;
	bool						m_isLooping;


	// TODO; store keyframes??
};


//struct BaseComponentData
//{
//	virtual ~BaseComponentData() {}
//};
//
//
//template <typename Derived>
//struct ComponentData
//{
//	Derived* Get()
//	{
//		return static_cast<Derived*>(this);
//	}
//};
//
//
//struct TransformComponentData : public ComponentData<TransformComponentData>
//{
//	float m_x;
//	float m_y;
//};
//
//struct SpriteComponentData : public ComponentData<SpriteComponentData>
//{
//	std::string m_sprite;
//};