#pragma once
//#include "Entities/Entity.h"
#include "ECSTypes.h"

class ECS;

class Command
{
public:
	virtual ~Command() = default;

	virtual void Execute(Entity entity, ECS& ecs) = 0;
	virtual bool CanPerform(Entity entity, ECS& ecs) const = 0;

	virtual void Undo(Entity entity, ECS& ecs) {};
	virtual void UpdateCooldown(float deltaTime) {};
};