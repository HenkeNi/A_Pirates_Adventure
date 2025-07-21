#pragma once
#include <../Source/ECS/Systems/System.h>

namespace Hi_Engine
{
	class World;
}

class MovementSystem : public Hi_Engine::System
{
public:
	MovementSystem(Hi_Engine::World& world);

	void Update(float deltaTime) override;
};

