#pragma once
#include "../Base/System.h"

class Entity;

class MovementSystem : public System
{
public:
	MovementSystem();
	~MovementSystem();

	void				Receive(Message& aMsg)		override;
	void				Update(float aDeltaTime)	override;

	static bool			HasMoved(const Entity* anEntity);


	// void InitComponents();  - possible!

private:
	void				UpdateColliders(Entity* anEntity, struct TransformComponent* aTransformComponent, struct VelocityComponent* aVelocityComponent);
};