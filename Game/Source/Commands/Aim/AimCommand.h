#pragma once
#include "../Base/Command.h"

// ToggleAimCommand?
class AimCommand : public Command
{
public:
	AimCommand(ECS& ecs);

	void Execute(Entity entity) override;
	void Undo(Entity entity) override;
	bool CanPerform(Entity entity) const override;

private:
	//bool m_shouldAim;
};