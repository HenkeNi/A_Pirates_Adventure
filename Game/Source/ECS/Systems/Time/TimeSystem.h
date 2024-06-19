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

	static FVector4 CalculateDaylightColor(Entity* worldTimeEntity); // filter system instead?

private:
	void UpdateWorldTime(float deltaTime);
	void SetTimeOfDay(Entity* worldTimeEntity);

	void UpdateTimers(float deltaTime);
};