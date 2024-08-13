#pragma once
#include "../Base/System.h"


class PhysicsSystem : public System, public Subscriber
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void Receive(Message& message)		override;
	void LateUpdate(float deltaTime)	override;
	void SetSignature()					override;

private:
	void ApplyVelocities();
	void UpdatePositions();
};