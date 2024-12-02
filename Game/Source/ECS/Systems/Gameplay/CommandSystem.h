#pragma once
#include "../Base/System.h"


class CommandSystem : public System
{
public:
	CommandSystem();
	~CommandSystem();

	void Update(float deltaTime) override;
	void SetSignature()	override;

private:
	void ProcessCommands(Entity entity);

	void HandleMoveCommand(Entity entity, const struct MovementData& data);
	void HandleSprintCommand(Entity entity, const struct SprintData& data);

	void HandleAttackCommand(Entity entity);
	void HandleProjectileCommand(Entity entity);
};