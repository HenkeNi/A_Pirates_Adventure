#pragma once
#include "../Base/System.h"


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
};