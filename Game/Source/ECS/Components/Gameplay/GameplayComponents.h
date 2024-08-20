#pragma once
#include "Stat.hpp"


//#################### Character Components ####################//
struct AttributesComponent
{
	int Perception = 5;
};

struct PersonalityComponent
{
	bool IsLoyal = false;
	bool IsFriendly = false;
	bool IsHonest = false;
	bool IsNervous = false;
	bool IsHelpful = false;
	bool IsCompetent = false;
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

struct CharacterStateComponent
{
	bool IsIdle;
	bool IsWalking;
	bool IsRunning;
	bool IsAttacking;
	bool IsAlive;
	bool IsAiming;
};

struct StaminaComponent
{
	unsigned MaxStamina;
	int CurrentValue;
};

struct HealthComponent // stats component instead?
{
	// Stat<int>		HealthStat;
	int				MaxHealth = 100;
	int				CurrentValue = 100; // make sure is updated when removing modifiers
	bool			IsInvincible;

	// TODO; store active effects? Or have an effect component?
};

struct PhysicalNeeds
{
	std::unordered_map<std::string, float> Needs;
};



//#################### Crafting Components ####################//
struct RecipeComponent
{
	std::string CraftedItem;
	std::unordered_map<std::string, unsigned> RequiredItems;
};

struct ResourceComponent // Remove?
{
	std::string ResourceType;
	// unsigned	m_quantity;
};

struct HarvestableComponent
{
	std::string ResourceType;
	int			Yield;
};

// Replace with ItemSpawner??
struct ResourceProducerComponent
{
	std::string		DroppedResource;
	unsigned		Quantity;
};



//#################### Controller Components ####################//
struct PlayerControllerComponent
{
	std::unordered_map<Hi_Engine::eKey, class Command*> InputMapping;
};




// Stats such as Health, Stamina, Armor(?), Regeneration -> separate stat components or all in one?

//struct StatsComponent : public ComponentBase
//{
//	std::unordered_map<std::string, StatModifier<float>>		m_floatStats;
//	std::unordered_map<std::string, StatModifier<unsigned>>		m_intStats;
//};

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
	//const float Duration = 0.25f;
	float Duration = 0.25f;
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




// rename SpawnerComponent?
struct SpawnComponent
{
	std::string Spawned;
	float		SpawnRadius = 30.f;
	float		Interval = 2.f;	// Todo; Give small individual delay..
	float		ElapsedTime = 0.f;
	int			Amount = 10;
	int			SpawnedAmount = 0; // Rename..

	// bool repeat; ?
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