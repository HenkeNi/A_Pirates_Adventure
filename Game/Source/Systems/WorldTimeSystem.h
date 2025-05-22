#pragma once
#include <../Source/ECS/Systems/System.h>

namespace Hi_Engine
{
	class World;
}

struct WorldTimeComponent;

class WorldTimeSystem : public Hi_Engine::System
{
public:
	WorldTimeSystem(Hi_Engine::World& world);

	void Update(float deltaTime) override;
	Hi_Engine::eUpdatePhase GetUpdatePhase() const override;

private:
	void AdvanceTime(WorldTimeComponent& component, float deltaTime);
	void UpdateDayProgress(WorldTimeComponent& component);
	void UpdateTimeOfDay(WorldTimeComponent& component);
};

