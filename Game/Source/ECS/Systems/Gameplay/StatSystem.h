#pragma once
#include "../Base/System.h"

// TODO; handle level up? exp points...

class StatSystem : public System, public Subscriber // StatsSystem?
{
public:
	StatSystem();
	~StatSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
};