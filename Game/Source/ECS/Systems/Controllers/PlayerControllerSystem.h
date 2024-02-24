#pragma once
#include "../Base/System.h"

class Entity;

class PlayerControllerSystem : public System
{
public:
	PlayerControllerSystem();
	~PlayerControllerSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

	// Static function for getting player position? or just use blackboard?

private:
	void ProcessCommands(Entity* anEntity);
	void CleanUpCommands();

	void UpdateCooldowns(Entity* anEntity);
	void UpdatePlayerState(Entity* anEntity);
};