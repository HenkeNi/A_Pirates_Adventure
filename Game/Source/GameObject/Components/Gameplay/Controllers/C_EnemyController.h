#pragma once
#include "../../Component.h"

class Behavior;	// rename SteeringBehavior?

class C_EnemyController : public Component
{
public:
	C_EnemyController(GameObject* anOwner = nullptr);

	void						HandleMessage(const CompMessage& aMsg)	override;
	void						Update(float aDeltaTime)				override;




private:
	Behavior* m_activeBehavior; // Or statemachine/decision tree? or state machine sets the behavior??
};