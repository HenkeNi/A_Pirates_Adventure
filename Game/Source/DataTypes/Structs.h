#pragma once
#include "Enumerations.h"
#include <any>
//#include <Hi_Engine.h> // Fix
#include  <../Core/Math/Vectors/Vector.hpp>
#include  <../Rendering/Material/Material.h>
#include  <../Rendering/Texture/Subtexture2D.h>


/// using namespace Hi_Engine::Math;
// Todo; change naming convention to sceneManager, rather thna m_sceneManager;

struct SharedContext
{
	// SceneManagerProxy		SceneManager;
	//class SystemManager&	SystemManager;
};


struct CollisionData // Data used for resolving/handling collisions
{
	// std::vector<Entity> CollidingEntities;

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
	std::shared_ptr<class Hi_Engine::Subtexture2D>  Subtexture; // NEED TO STORE? store weak ref?
	//class Hi_Engine::Subtexture2D*  Subtexture; // NEED TO STORE? store weak ref?

	FVector4						Color  = { 1.f, 1.f, 1.f, 1.f }; // DO ELSEWHER!?
	FVector2						Position;			// store chunk coordiante instead?
	UVector2						Coordinates;			// Use only one!!
	eTile							Type;
	bool							IsTraversable;
	static constexpr float Size = 64.f;
	//static constexpr float Size = 32.f;
};

// Put in Engine?? => wrap a texture instead?? => specify coordiantes and stuff...
//

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