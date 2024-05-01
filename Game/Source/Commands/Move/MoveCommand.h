#pragma once
#include "../Base/Command.h"


class MoveCommand : public Command	// derive from EntityCommand? (GlobalCommand)
{
public:
	MoveCommand();
	MoveCommand(const FVector2& direction);

	void Execute(Entity* entity)		  override;
	bool CanPerform(Entity* entity) const override;

private:
	FVector2			m_direction;
};
