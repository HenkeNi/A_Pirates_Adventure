#pragma once
#include "../Base/ComponentBase.h"

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