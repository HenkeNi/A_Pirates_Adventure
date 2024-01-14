#pragma once
#include "../Base/System.h"


class TimeSystem : public System
{
public:
	TimeSystem();
	~TimeSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:
	float GetAverageDeltaTime(float aDeltaTime) const;
};