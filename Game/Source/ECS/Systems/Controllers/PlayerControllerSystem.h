#pragma once
#include "../Base/System.h"

class Entity;

class PlayerControllerSystem : public System, public Subscriber
{
public:
	PlayerControllerSystem();
	~PlayerControllerSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

	// Static function for getting player position? or just use blackboard?

private:
	void ProcessCommands(Entity* entity);
	void CleanUpCommands();

	void UpdateCooldowns(Entity* entity);
	void UpdatePlayerState(Entity* entity);
};