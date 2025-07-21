#pragma once
#include <../Source/ECS/Systems/System.h>

class InventorySystem : public Hi_Engine::System
{
public:
	InventorySystem(Hi_Engine::World& world);
};
