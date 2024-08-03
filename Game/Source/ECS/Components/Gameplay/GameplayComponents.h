#pragma once
#include "Stat.hpp"


//#################### Character Components ####################//
struct AttributesComponent
{
	int Perception = 5;

	// std::unordered_map<std::string, Stat<int>>		m_attributes;
};

// Rename TraitComponent?
struct PersonalityComponent
{
	bool IsAggressive = false;
	// bool IsFriendly = false;
	// bool IsHostile = false;
	// bool IsLoyal = false;
};

struct FriendlyComponent
{
};

struct HostileComponent
{
};

struct CrewComponent
{
};

// Rename? PlayerStateComponent, should just be used by the player??
struct CharacterStateComponent
{
	bool IsIdle;
	bool IsWalking;
	bool IsRunning;
	bool IsAttacking;
	bool IsAlive;		// remove?
	bool IsAiming;
};





//#################### Crafting Components ####################//
struct RecipeComponent
{
	std::string CraftedItem;
	std::unordered_map<std::string, unsigned> RequiredItems;
};





// TreeResourceComponent
struct ResourceComponent
{
	//std::string m_entityToCreate = "TreeResource";	// FIX!
	// std::string m_entityToCreate = "Resource";	// FIX!

	// TODO; 
	std::string ResourceType;
	// unsigned	m_quantity;
};



// Harvest system?? HarvetableComponent  ResourceSpawnerComponent

// maybe remove??? or use for fruit trees, etc?
struct HarvestableComponent
{
	std::string ResourceType;	 // Rename??
	int			Yield;
};


// Replace with ItemSpawner??
struct ResourceProducerComponent
{
	std::string		DroppedResource;
	unsigned		Quantity;
};














/* - Controllers - */ // MOVE THIS 0> Not ai...	

struct PlayerControllerComponent
{
	//std::unordered_map<KeyStatus, class Command*> InputMapping;
	std::unordered_map<Hi_Engine::eKey, class Command*> InputMapping; // TODO; rename, move Command from engine?
	// - Input/Gamepad mappings -> key, command?
	// COmmands..
};






// SpriteSheet component? (stores texture atlas, also holds current frame, etc...)

// Shadow component??


// Stats such as Health, Stamina, Armor(?), Regeneration -> separate stat components or all in one?

//struct StatsComponent : public ComponentBase
//{
//	std::unordered_map<std::string, StatModifier<float>>		m_floatStats;
//	std::unordered_map<std::string, StatModifier<unsigned>>		m_intStats;
//};

// Rename attributes?

struct HealthComponent
{
	Stat<int>		HealthStat; // DONT!?

	int MaxHealth = 100;
	// unsigned		m_maxHealth; // renaem?
	int				CurrentValue = 100; // make sure is updated when removing modifiers... (100 is just temp -> init somewhere)...
	bool			IsInvincible;

	// TODO; store in effects? Or have an effect component?

};

struct StaminaComponent
{
	unsigned MaxStamina;
	int CurrentValue;
	// bool m_is;
};





// HERE??? or Needed???
struct PhysicalNeeds
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













// Dont have health? Use Stats Component instead?
//struct HealthComponent : public ComponentBase
//{
//	int		m_maxHealth;
//	int		m_currentHealth;
//};



/* ######################### Equipment ######################### */
struct EquipmentComponent
{
	std::array<int, (int)eEquipmentSlot::Count> EquippedItemIDs; // Stores ID's of equiped items (-1 == nothing equiped) => entity id or item id (read from json)?
};

struct EquippableComponent
{
	eEquipmentSlot AcceptableSlot; // TODO; read from json
	bool IsEquipped = false; // NEEDED?
};

// Consider: Merging the Equipment into the InventoryComponent?
struct InventoryComponent
{
	static constexpr unsigned MaxSlots = 36;
	std::array<InventorySlot, MaxSlots> Slots;
	unsigned UnlockedSlots = 12;

	bool IsOpen = false;

	UVector2 GridDimensions;

	// std::unordered_map<std::string, unsigned> Inventory; // Or list of entities? or list of ItemComponents?

	// unsigned MaxCapacity; // every item has a weight? or save available slots
	// unsigned AvailableSpace;
};

struct CollectableComponent
{
	Item	Item;
	double	SpawnTimestamp;
	float	PickupDelay;
	bool	IsCollected = false;
	//std::string ItemID;
};


/* ######################### Combat ######################### */
struct AttackComponent
{
	// Hi_Engine::Physics::AABB2D<float>	Collider;
	// CU::Vector2<float>					Offset = { 20.f, 20.f };
	// circle collider?
	// bool								IsEnabled;
};

struct AttackCooldownComponent
{
	const float Duration = 0.25f;
	float Remaining = 0.f;
};

struct WeaponComponent // gun component?
{
	float	AttackRange;
	float	AttackSpeed;
	int		DamageDealt  = 10;

	// enum daamge type (explosive, slashing, blunt
};

//struct GunComponent : public Component
//{
//
//};
//
//struct SwordComponent : public Component
//{
//
//};

struct ProjectileComponent
{
	double Timestamp;
	float LifeTime = 3.f;
};

struct ExplosionComponent
{};

struct KnockbackComponent
{
	FVector2 Direction;
	float Power;
	double Timestamp;
	float Duration;	
};

struct VisionComponent
{
	Hi_Engine::Physics::LineSegment2D<float> LineOfSight;
};




// MOVE

// reanem SpawnComponent?
struct SpawnerComponent
{
	std::string Spawned;// SpawnableBlueprintID; // ID to entity to create
	int			Amount;
	bool		IsReadyToSpawn; // Spawn type (on death, on hit)???

	// bool IsRepeating? or make its own component? Repating Spwaner
};

struct EnemySpawnerComponent
{
};

struct ItemSpawnerComponent
{
};


struct EnvironmentComponent
{
	// static std::vector<eTile> AcceptableTileTypes; // remove?
};





// Topple? Fall, FallOver OR just a Tree Component?  EnvironemnetComponent ResourceComponent? TreePhysics System?
struct ToppleComponent
{

};

struct ShakeComponent
{
	bool m_isShaking = false;
	//float m_timestamp = 0.f;
	float m_duration = 0.25f;
	float m_elapsedTime = 0.f;
};