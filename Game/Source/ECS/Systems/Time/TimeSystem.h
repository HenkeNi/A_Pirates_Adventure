#pragma once
#include "../Base/System.h"


class TimeSystem : public System
{
public:
	TimeSystem();
	~TimeSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

private:
	float GetAverageDeltaTime(float deltaTime) const;

	void UpdateWorldTime(float deltaTime);
	void UpdateTimers(float deltaTime);
};