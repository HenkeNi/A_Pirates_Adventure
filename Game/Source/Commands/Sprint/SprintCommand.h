#pragma once
#include "../Base/Command.h"

class SprintCommand : public Command
{
public:
	SprintCommand();

	void Execute(Entity* entity)		  override;
	bool CanPerform(Entity* entity)	const override;

	void Undo(Entity* entity)			  override;

private:
	float m_sprintSpeed; // HERE?
	//float m_sprintSpeedMultiplier; // HERE?
};