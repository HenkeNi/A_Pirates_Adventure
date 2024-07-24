#pragma once
#include "../Base/System.h"


class MovementSystem : public System, public Subscriber
{
public:
	MovementSystem();
	~MovementSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

	static bool	HasMoved(Entity entity);
	static bool IsKnockbacked(Entity entity); //or move to movemnt sysyem, is being knockedback

private:
	void MoveSubEntities(Entity entity);
	void ApplyKnockback(Entity entity);
};