#pragma once
#include <../Source/ECS/Systems/System.h>

class PlayerControllerSystem : public Hi_Engine::System
{
public:
	PlayerControllerSystem(Hi_Engine::World& world);
};