#pragma once
#include "../Base/Command.h"

//namespace CU = CommonUtilities;

class MoveCommand : public Command	// derive from EntityCommand? (GlobalCommand)
{
public:
	MoveCommand();
	MoveCommand(const CU::Vector2<float>& aDirection);

	void Execute(Entity* entity)		  override;
	bool CanPerform(Entity* entity) const override;

private:
	CU::Vector2<float>			m_direction;
};
