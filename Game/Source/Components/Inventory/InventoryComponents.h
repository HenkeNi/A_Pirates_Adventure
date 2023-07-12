#pragma once
#include "../ComponentBase.h"


struct InventoryComponent : public ComponentBase
{
	std::unordered_map<std::string, unsigned> m_inventory;
	// array of entiity pointers (or IDs)..??

	unsigned m_maxCapacity; // every item has a weight?
	unsigned m_currentCapacity;
};