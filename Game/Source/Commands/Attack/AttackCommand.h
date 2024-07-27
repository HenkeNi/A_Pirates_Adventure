#pragma once
#include "../Base/Command.h"

class AttackCommand : public Command
{
public:
	AttackCommand();

	void Execute(Entity entity, ECS& ecs)			override;
	bool CanPerform(Entity entity, ECS& ecs) const override;

private:
	// Cooldown struct?
	float m_cooldown;
	float m_cooldownDuration;
};