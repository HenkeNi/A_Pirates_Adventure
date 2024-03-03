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

private:
	void MoveSubEntities(Entity* anEntity);
};