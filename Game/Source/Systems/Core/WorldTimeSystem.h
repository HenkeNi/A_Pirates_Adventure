#pragma once
#include <../Source/ECS/Systems/System.h>

namespace Hi_Engine
{
	class World;
}

struct WorldTimeComponent;

class WorldTimeSystem : public Hi_Engine::System, public Subscriber
{
public:
	WorldTimeSystem(Hi_Engine::World& world);
	~WorldTimeSystem();

	void Receive(Message& message) override; // just for test...
	void Update(float deltaTime) override;

	void OnCreated() override;

private:
	void AdvanceTime(WorldTimeComponent& component, float deltaTime);
	void UpdateDayProgress(WorldTimeComponent& component);
	void UpdateTimeOfDay(WorldTimeComponent& component);
};

