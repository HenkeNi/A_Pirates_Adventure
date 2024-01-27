#pragma once
#include "../Base/Command.h"

class SprintCommand : public Command
{
public:
	SprintCommand();

	void Execute(Entity* anEntity)			override;
	bool CanPerform(Entity* anEntity) const override;

private:
	float m_sprintSpeed; // HERE?
};