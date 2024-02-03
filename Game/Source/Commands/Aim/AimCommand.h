#pragma once
#include "../Base/Command.h"

// ToggleAimCommand?
class AimCommand : public Command
{
public:
	AimCommand();

	void Execute(Entity* anEntity)			override;
	void Undo(Entity* anEntity)				override;
	bool CanPerform(Entity* anEntity) const override;

private:
	//bool m_shouldAim;
};