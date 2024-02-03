#pragma once
#include "../Base/Command.h"

class SprintCommand : public Command
{
public:
	SprintCommand();

	void Execute(Entity* anEntity)			override;
	bool CanPerform(Entity* anEntity) const override;

	void Undo(Entity* anEntity)				override;

private:
	float m_sprintSpeed; // HERE?
};