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
	SceneManagerProxy		SceneManager;
	class SystemManager&	SystemManager;
};


struct CollisionData // Data used for resolving/handling collisions
{
	unsigned DamageDealt = 0;
};

template <typename T>
struct Range
{
	T Min;
	T Max;
};


struct Tile
{
	//Hi_Engine::Material m_material;
	class Hi_Engine::Subtexture2D* Subtexture;
	CU::Vector4<float>	Color  = { 1.f, 1.f, 1.f, 1.f }; // DO ELSEWHER!?
	CU::Vector3<float>	Position;			// store chunk coordiante instead?
	CU::Vector2<int>	Coordinates;			// Use only one!!
	eTile				Type;
	bool				IsCollidable;
};

// Put in Engine??
struct Animation
{
	std::vector<std::string>	Sprites;
	unsigned					TotalFrames;
	unsigned					CurrentFrame;
	float						FrameDuration;
	float						ElapsedFrameTime;
	bool						IsPlaying;
	bool						IsLooping;


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