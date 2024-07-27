#pragma once
#include "../Base/Command.h"

class SprintCommand : public Command
{
public:
	SprintCommand();

	void Execute(Entity entity, ECS& ecs)		  override;
	bool CanPerform(Entity entity, ECS& ecs)	const override;

	void Undo(Entity entity, ECS& ecs)			  override;

private:
	float m_sprintSpeed; // HERE?
	//float m_sprintSpeedMultiplier; // HERE?
};