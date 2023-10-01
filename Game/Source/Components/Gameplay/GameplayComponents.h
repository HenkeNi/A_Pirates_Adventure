#pragma once
#include "../Base/ComponentBase.h"



struct TriggerComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
};


struct PickupColliderComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
};


struct ItemComponent : public ComponentBase
{
	std::string Identifier;
	std::string IconTexture;
};

struct EquipmentComponent : public ComponentBase
{};


struct InventoryComponent : public ComponentBase
{
	std::unordered_map<std::string, unsigned> Inventory; // Or list of entities? or list of ItemCOmponents?
	// array of entiity pointers (or IDs)..??

	unsigned MaxCapacity; // every item has a weight?
	unsigned CurrentCapacity;
};



struct RecipeComponent : public ComponentBase
{
	std::string CraftedItem;
	std::unordered_map<std::string, unsigned> RequiredItems;
};



// TreeResourceComponent
struct ResourceComponent : ComponentBase
{
	//std::string m_entityToCreate = "TreeResource";	// FIX!
	// std::string m_entityToCreate = "Resource";	// FIX!

	// TODO; 
	std::string ResourceType;
	// unsigned	m_quantity;
};



// Harvest system?? HarvetableComponent  ResourceSpawnerComponent

struct HarvestableComponent : ComponentBase
{
	std::string ResourceType;	 // Rename??
	int			Yield;
};


// Replace with ItemSpawner??
struct ResourceProducerComponent : ComponentBase
{
	std::string		DroppedResource;
	unsigned		Quantity;
};