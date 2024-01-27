#pragma once
#include "../Base/Command.h"

class AttackCommand : public Command
{
public:
	AttackCommand();

	void Execute(Entity* anEntity)			override;
	bool CanPerform(Entity* anEntity) const override;
};