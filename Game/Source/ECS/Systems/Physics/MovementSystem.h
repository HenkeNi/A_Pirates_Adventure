#pragma once
#include "../Base/System.h"

class Entity;

class MovementSystem : public System
{
public:
	MovementSystem();
	~MovementSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

	static bool	HasMoved(const Entity* anEntity);
	static bool IsKnockbacked(Entity* anEntity); //or move to movemnt sysyem, is being knockedback

private:
	void MoveSubEntities(Entity* anEntity);
	void ApplyKnockback(Entity* anEntity);
};