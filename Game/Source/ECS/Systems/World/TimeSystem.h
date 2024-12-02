#pragma once
#include "../Base/System.h"

struct WorldTimeComponent;

class TimeSystem : public System
{
public:
	TimeSystem();
	~TimeSystem();

	void Update(float deltaTime) override;
	void SetSignature() override;

private:
	void UpdateWorldTime(float deltaTime);
	void UpdateTimers(float deltaTime);

	void AdvanceTime(WorldTimeComponent& worldTime, float deltaTime);
	void UpdateDayProgress(WorldTimeComponent& worldTime);
	void UpdateTimeOfDay(WorldTimeComponent& worldTime);
};