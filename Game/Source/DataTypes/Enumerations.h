#pragma once



enum class eMessage
{
	EntityCreated,
	EntitiesCollided,

	// EntityCollected,

	EntityDestroyed,
	//EntityDied,				// just destroyed?
	EntityAttacked,				// rename AttackEvent? AttackBegan? AttackEnded?

	EntityAttacking, // rename?

	EntityWalking, // REMOVE?
	EntityIdle,		// REMOVE?

	EntityFired,

	EntityEnteredAim,
	EntityExitedAim,

	ItemEquipped,
	ItemUnequipped,

	PlayerLeveledUp,

	//AttackFinished,
	AnimationComplete,
	
	AttackAnimationFinished,

	GameStarted,

	TimeOfDayChanged,

	TriggerActivated,
	ButtonActivated,
	TimerFinished,

	ItemCollected, // PickedUp instead??
	ItemUsed,

	TransitionToScene,
	// RemoveScene,
	// MapChunkCreated,
	//MapChunkDestroyed

	// TEMP
	EnemyAttacked,

	IsSelected, // ? For editor?
	MouseClicked
};

enum class eLayer
{
	Terrain,
	Characters,
	Items,
	Buildings,
	Effects,
	UI
};


enum class eBTNodeStatus
{
	Invalid,
	Success,
	Failure,
	Running
};

enum class eTile
{
	Grass, Sand, ShallowWater, Water, DeepWater, Void
};

enum class eMovementDir
{
	None,
	Up,
	Down,
	Left,
	Right,
	UpLeft,
	UpRight,
	DownLeft,
	DownRight
};

enum class eDirection
{
	Up,
	Down,
	Left,
	Right
};

enum class eDirectionalValue
{
	North = 1,
	West = 2,
	East = 4,
	South = 8
};

enum eCollisionLayer
{
	Default,
	Player,
	Friendly,
	Hostile,
	Projectiles,
	Obstacles,
	Collectibles,
	Triggers,
	Terrain,
	UI,
	Interactables,
};

enum class eColliderType
{
	Static,
	Dynamic,
	Trigger
};



enum class eAttributes	// or major stats
{
	// S C U M

	Strength,	// Physical Strength
	Charisma,
	Luck,


	Constitution,	// Enduramce`?
	Agility,	// Dexterity?

	Cunning,		// inmte��ogemce
	Willpower,
	Explosives,

	Cool, 
	Violence,

	Fear // Liked? separate thing
};




enum class eSkills	// minor stats?
{
	FireResitance, // ??
	AttackSpeed,
	CriticalChance,
	WeaponDamage, // ??
	Dodge,
	Block,

};


enum class eEquipmentSlot
{
	Legs, 
	Torso, 
	Hat,
	Melee,
	Ranged,
	Throwable,
	Count
};