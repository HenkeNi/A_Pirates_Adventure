#pragma once
#include "../Base/Command.h"

// Or just one attack command?
class ShootCommand : public Command
{
public:
	ShootCommand();

	void Execute(Entity entity, ECS& ecs)		  override;
	bool CanPerform(Entity entity, ECS& ecs) const override;

private:
	double				m_timestamp;
	float				m_delayBetweenShots;
};