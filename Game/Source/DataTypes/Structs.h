#pragma once
#include "Enumerations.h"
#include <any>
//#include <Hi_Engine.h> // Fix
#include  <../../../Engine/Source/Utility/Math/Vectors/Vector.hpp>
#include  <../../../Engine/Source/Core/Rendering/Material/Material.h>
#include  <../../../Engine/Source/Core/Rendering/Texture/Subtexture2D.h>

/// using namespace Hi_Engine::Math;
// Todo; change naming convention to sceneManager, rather thna m_sceneManager;

struct SharedContext
{
	// SceneManagerProxy		SceneManager;
	//class SystemManager&	SystemManager;
};


struct CollisionData // Data used for resolving/handling collisions
{
	std::vector<class Entity*> CollidingEntities;

	//bool IsColliding = false;
	//class Entity* CollidingEntity = nullptr; // Store array of entities colliding with? Or array of colllision data  in component?

	// unsigned DamageDealt = 0;

	// std::array<class Entity*, 2> CollidingEntities = { nullptr, nullptr };

	//ColliderComponent* Collider;
	//class Entity* FirstEntity = nullptr; // Owner;
	//class Entity* SecondEntity = nullptr;

	// Or pass array of CollisionData?
	//ColliderComponent* Collider;
	//Entity* Entity;
};

struct Tile
{
	class Hi_Engine::Subtexture2D*  Subtexture; // NEED TO STORE?
	FVector4						Color  = { 1.f, 1.f, 1.f, 1.f }; // DO ELSEWHER!?
	FVector2						Position;			// store chunk coordiante instead?
	UVector2						Coordinates;			// Use only one!!
	eTile							Type;
	bool							IsCollidable;
	static constexpr float Size = 1.f;
};

// Put in Engine?? => wrap a texture instead?? => specify coordiantes and stuff...
struct Animation
{
	std::vector<class Hi_Engine::Subtexture2D*> Animations; // rename AnimationFrames or Frames
	// std::vector<std::string>	Sprites;
	unsigned					TotalFrames		= 0;
	unsigned					CurrentFrame	= 0;
	float						FrameDuration	= 0.f;
	float						ElapsedFrameTime = 0.f;
	bool						IsPlaying = false;
	bool						IsLooping = false;
	
	bool						IsInverted = false;


	// TODO; store keyframes??
};

struct ProjectileData
{
	FVector2 Position;
	FVector2 Directin;
	float	 Speed;
};

struct Item
{
	std::string ItemID = "Empty";		// replace with unsigned (read id's from json)
	unsigned	MaxStack;
	// bool		IsUnique;
};

struct InventorySlot
{
	Item		Item;
	unsigned	Quantity = 0;
};

struct Offset
{
	float XOffset;
	float YOffset;
	bool IsDirectionallyBound;
};

struct Color
{
	float R = 1.f;
	float G = 1.f;
	float B = 1.f;
	float A = 1.f;
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


struct KeyStatus
{
	Hi_Engine::eKey Key;
	Hi_Engine::eInputState State;
};

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




struct StateData
{
	class Entity* Owner;
	float ElapsedTime;
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