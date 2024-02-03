#pragma once

class Entity;

class Command
{
public:
	virtual ~Command() = default;

	virtual void Execute(Entity* anEntity) = 0;
	virtual bool CanPerform(Entity* anEntity) const = 0; 

	virtual void Undo(Entity* anEntity) {};
	virtual void UpdateCooldown(float aDeltaTime) {};
};