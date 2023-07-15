#pragma once
#include "Base/System.h"


class MovementSystem : public System
{
public:
	MovementSystem();
	~MovementSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

	// void InitComponents();  - possible!


	// All components that have transform and velocity...

private:
	void UpdatePosition();


	bool HasMoved(class TransformComponent* aTransform) const;

};

	