#pragma once
#include "../Base/System.h"

class Entity;

class TimeSystem : public System
{
public:
	TimeSystem();
	~TimeSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

	// static float	CalculateDayProgression(Entity* worldTimeEntity); // maybe get component instead?
	static FVector4 CalculateDaylightColor(Entity* worldTimeEntity); // filter system instead?

private:
	void UpdateWorldTime(float deltaTime);
	void SetTimeOfDay(Entity* worldTimeEntity);

	//float GetAverageDeltaTime(float deltaTime) const;

	void UpdateTimers(float deltaTime);
};