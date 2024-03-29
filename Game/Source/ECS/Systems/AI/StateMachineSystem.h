#pragma once
#include "../Base/System.h"

class Entity;

class StateMachineSystem : public System
{
public:
	StateMachineSystem();
	~StateMachineSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

private:
	void UpdateCurrentState(Entity* entity);
};