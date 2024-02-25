#pragma once
#include "../Base/Component.h"

#include "Stat.hpp"


struct PickupColliderComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
};

struct ItemComponent : public Component
{
	std::string Identifier;
	std::string IconTexture;
};

struct EquipmentComponent : public Component
{};


struct InventoryComponent : public Component
{
	std::unordered_map<std::string, unsigned> Inventory; // Or list of entities? or list of ItemCOmponents?
	// array of entiity pointers (or IDs)..??

	unsigned MaxCapacity; // every item has a weight?
	unsigned CurrentCapacity;
};



struct RecipeComponent : public Component
{
	std::string CraftedItem;
	std::unordered_map<std::string, unsigned> RequiredItems;
};



// TreeResourceComponent
struct ResourceComponent : public Component
{
	//std::string m_entityToCreate = "TreeResource";	// FIX!
	// std::string m_entityToCreate = "Resource";	// FIX!

	// TODO; 
	std::string ResourceType;
	// unsigned	m_quantity;
};



// Harvest system?? HarvetableComponent  ResourceSpawnerComponent

struct HarvestableComponent : public Component
{
	std::string ResourceType;	 // Rename??
	int			Yield;
};


// Replace with ItemSpawner??
struct ResourceProducerComponent : public Component
{
	std::string		DroppedResource;
	unsigned		Quantity;
};








// HERE?? Or maybe use two sprites instead?? add system HealthBarSystem?
struct HealthBarComponent : public Component
{
	Hi_Engine::Material Container;
	Hi_Engine::Material Bar;
	// position? size?
};





struct AttributeComponent : public Component
{
	// contains 
	// std::unordered_map<std::string, Stat<int>>		m_attributes;

};


/* - Controllers - */ // MOVE THIS 0> Not ai...	
struct KeyStatus
{
	Hi_Engine::eKey Key;
	Hi_Engine::eInputState State;
};

struct PlayerControllerComponent : public Component
{
	//std::unordered_map<KeyStatus, class Command*> InputMapping;
	std::unordered_map<Hi_Engine::eKey, class Command*> InputMapping; // TODO; rename, move Command from engine?
	// - Input/Gamepad mappings -> key, command?
	// COmmands..
};


// Rename? PlayerStateComponent, EntityState, StateComponent?
struct CharacterStateComponent : public Component
{
	bool IsIdle;
	bool IsWalking;
	bool IsRunning;
	bool IsJumping;
	bool IsAttacking;
	bool IsAlive;

	bool IsAiming;
	// State machine??
};


struct CrosshairComponent : public Component
{
	// target?
};


// SpriteSheet component? (stores texture atlas, also holds current frame, etc...)




// Shadow component??




// REMOVE!!!
//struct TileComponent : public ComponentBase
//{
//	// Tile specific data..
//	CU::Vector2<float>	m_size;
//	unsigned			m_type;		
//	bool				m_isTraversable; // Needed???
//};
//
//struct MapChunkComponent : public ComponentBase
//{
//	CU::Vector2<unsigned>	m_size;
//	CU::Vector2<int>		m_position;
//	unsigned				m_chunkID;
//
//
//	// Data for chunk of tiles
// };

// Store each tile as an Entity? depending on which chunk it is in => render it or not..???










// Stats such as Health, Stamina, Armor(?), Regeneration -> separate stat components or all in one?

//struct StatsComponent : public ComponentBase
//{
//	std::unordered_map<std::string, StatModifier<float>>		m_floatStats;
//	std::unordered_map<std::string, StatModifier<unsigned>>		m_intStats;
//};

// Rename attributes?

struct HealthComponent : public Component
{
	Stat<int>		HealthStat; // DONT!?

	// unsigned		m_maxHealth; // renaem?
	int				CurrentValue = 100; // make sure is updated when removing modifiers... (100 is just temp -> init somewhere)...
	bool			IsInvincible;

	// TODO; store in effects? Or have an effect component?

};

struct StaminaComponent : public Component
{
	unsigned MaxStamina;
	int CurrentValue;
	// bool m_is;
};





// HERE??? or Needed???
struct PhysicalNeeds : public Component
{
	std::unordered_map<std::string, float> Needs;

};


//enum class eModifierType
//{
//	Coefficient,
//	PreAdditive,
//	PostAdditive
//};

//template <typename T>
//struct Modifier
//{
//	enum class eModifierType
//	{
//		Coefficient,
//		PreAdditive,
//		PostAdditive
//	} m_type;
//	std::string		m_identifier;
//	T m_value;
//};


struct HitboxComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider; // or use circle...
	bool								IsStatic;
};

struct AttackComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
	CU::Vector2<float>					Offset = { 20.f, 20.f };
	// circle collider?
	bool								IsEnabled;
};













// Dont have health? Use Stats Component instead?
//struct HealthComponent : public ComponentBase
//{
//	int		m_maxHealth;
//	int		m_currentHealth;
//};


// Place in equipment??

struct WeaponComponent : public Component
{
	float	AttackRange;
	float	AttackSpeed;
	int		DamageDealt;
};

struct ProjectileComponent : public Component
{
	double Timestamp;
	float LifeTime = 3.f;
};


// gun component?

// bullet component?

// place in Physics??






// MOVE

// reanem SpawnComponent?
struct SpawnerComponent : public Component
{
	std::string Spawned;// SpawnableBlueprintID; // ID to entity to create
	int			Amount;
	bool		IsReadyToSpawn;
};



struct EnemySpawnerComponent : public Component
{

};



struct ItemSpawnerComponent : public Component
{

};








// Topple? Fall, FallOver OR just a Tree Component?  EnvironemnetComponent ResourceComponent? TreePhysics System?
struct ToppleComponent : public Component
{

};

struct ShakeComponent : public Component
{
	bool m_isShaking = false;
	//float m_timestamp = 0.f;
	float m_duration = 0.25f;
	float m_elapsedTime = 0.f;
};

// For stones?
struct ExplosionComponent : public Component
{};