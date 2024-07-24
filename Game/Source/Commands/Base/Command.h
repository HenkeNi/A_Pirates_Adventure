#pragma once
#include "Entities/Entity.h"

class Command
{
public:
	virtual ~Command() = default;

	virtual void Execute(Entity entity) = 0;
	virtual bool CanPerform(Entity entity) const = 0;

	virtual void Undo(Entity entity) {};
	virtual void UpdateCooldown(float deltaTime) {};
};