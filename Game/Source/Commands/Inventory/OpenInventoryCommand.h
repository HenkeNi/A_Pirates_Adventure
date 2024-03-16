#pragma once
#include "../Base/Command.h"


class OpenInventoryCommand : public Command
{
public:
	OpenInventoryCommand();

	void Execute(Entity* anEntity) override;
	bool CanPerform(Entity* anEntity) const override;

private:

};