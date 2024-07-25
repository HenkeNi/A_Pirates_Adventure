#pragma once
#include "../Base/System.h"


class TimeSystem : public System
{
public:
	TimeSystem();
	~TimeSystem();

	void Update(float deltaTime)	override;
	void SetSignature() override;

	//static FVector4 CalculateDaylightColor(Entity worldTimeEntity); // filter system instead?

private:
	void UpdateWorldTime(float deltaTime);
	// void SetTimeOfDay(Entity worldTimeEntity);

	void UpdateTimers(float deltaTime);
};