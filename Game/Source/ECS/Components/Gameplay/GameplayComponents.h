#pragma once
#include "../Base/Component.h"



struct TriggerComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
};


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
struct ResourceComponent : Component
{
	//std::string m_entityToCreate = "TreeResource";	// FIX!
	// std::string m_entityToCreate = "Resource";	// FIX!

	// TODO; 
	std::string ResourceType;
	// unsigned	m_quantity;
};



// Harvest system?? HarvetableComponent  ResourceSpawnerComponent

struct HarvestableComponent : Component
{
	std::string ResourceType;	 // Rename??
	int			Yield;
};


// Replace with ItemSpawner??
struct ResourceProducerComponent : Component
{
	std::string		DroppedResource;
	unsigned		Quantity;
};