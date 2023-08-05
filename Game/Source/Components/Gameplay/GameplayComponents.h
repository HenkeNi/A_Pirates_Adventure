#pragma once
#include "../Base/ComponentBase.h"



struct TriggerComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float>	m_collider;
};


struct PickupColliderComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float>	m_collider;
};


struct ItemComponent : public ComponentBase
{
	std::string m_identifier;
	std::string m_iconTexture;
};

struct EquipmentComponent : public ComponentBase
{};


struct InventoryComponent : public ComponentBase
{
	std::unordered_map<std::string, unsigned> m_inventory; // Or list of entities? or list of ItemCOmponents?
	// array of entiity pointers (or IDs)..??

	unsigned m_maxCapacity; // every item has a weight?
	unsigned m_currentCapacity;
};



struct RecipeComponent : public ComponentBase
{
	std::string m_craftedItem;
	std::unordered_map<std::string, unsigned> m_requiredItems;
};



// TreeResourceComponent
struct ResourceComponent : ComponentBase
{
	//std::string m_entityToCreate = "TreeResource";	// FIX!
	// std::string m_entityToCreate = "Resource";	// FIX!

	// TODO; 
	std::string m_resourceType;
	// unsigned	m_quantity;
};



// Harvest system?? HarvetableComponent  ResourceSpawnerComponent

struct HarvestableComponent : ComponentBase
{
	std::string m_resourceType;	 // Rename??
	int			m_yield;
};


// Replace with ItemSpawner??
struct ResourceProducerComponent : ComponentBase
{
	std::string		m_droppedResource;
	unsigned		m_quantity;
};