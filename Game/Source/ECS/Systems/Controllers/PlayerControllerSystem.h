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

private:
	void ProcessCommands(Entity* anEntity);
	void UpdatePlayerState(Entity* anEntity);
};