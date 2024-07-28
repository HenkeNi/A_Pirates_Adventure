#pragma once
#include "../Base/System.h"


class PlayerControllerSystem : public System, public Subscriber
{
public:
	PlayerControllerSystem();
	~PlayerControllerSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

	void SetSignature() override;

private:
	void ProcessCommands(Entity entity);
	void CleanUpCommands();

	void UpdateCooldowns(Entity entity);
	void UpdatePlayerState(Entity entity);
};