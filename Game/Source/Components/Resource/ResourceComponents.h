#pragma once
#include "../ComponentBase.h"

// TreeResourceComponent
struct ResourceComponent : ComponentBase
{
	//std::string m_entityToCreate = "TreeResource";	// FIX!
	std::string m_entityToCreate = "Resource";	// FIX!
	unsigned	m_quantity;
};