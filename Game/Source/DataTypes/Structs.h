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
	CU::Vector2<float>	Position;			// store chunk coordiante instead?
	CU::Vector2<int>	Coordinates;			// Use only one!!
	eTile				Type;
	bool				IsCollidable;

	static constexpr float Size = 1.f;
};

// Put in Engine?? => wrap a texture instead?? => specify coordiantes and stuff...
struct Animation
{
	std::vector<class Hi_Engine::Subtexture2D*> Animations; // rename AnimationFrames or Frames
	// std::vector<std::string>	Sprites;
	unsigned					TotalFrames;
	unsigned					CurrentFrame;
	float						FrameDuration;
	float						ElapsedFrameTime;
	bool						IsPlaying;
	bool						IsLooping;
	
	bool						IsInverted;


	// TODO; store keyframes??
};

//struct AnimationSequence
//{ 
//	//class Hi_Engine::Subtexture2D*	Subtexture;
//	class Hi_Engine::Texture2D*		Texture;
//	unsigned						TotalFrames;
//	unsigned						CurrentFame;
//	float							FrameDuration;
//	float							ElapsedFrameTime;
//	bool							IsPlaying;
//	bool							IsLooping;
//
//
//	// wraps a subtexture... sets coordinates??
//};
//



//
//
//class Animation
//{
//public:
//	Animation();
//
//private:
//	class Hi_Engine::Texture2D* m_texture;
//	glm::vec2 m_coordinates[4]  m_texCoords;
//
//
//};







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