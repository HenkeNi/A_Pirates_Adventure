#pragma once
#include "../Base/System.h"


class WeatherSystem : public System
{
public:
	WeatherSystem();
	~WeatherSystem();

	void Update(float deltaTime) override;
};