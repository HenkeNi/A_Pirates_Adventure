#pragma once
#include "../Base/Command.h"

// ToggleAimCommand?
class AimCommand : public Command
{
public:
	AimCommand();

	void Execute(Entity entity, ECS& ecs)			override;
	void Undo(Entity entity, ECS& ecs)				override;
	bool CanPerform(Entity entity, ECS& ecs) const override;

private:
	//bool m_shouldAim;
};