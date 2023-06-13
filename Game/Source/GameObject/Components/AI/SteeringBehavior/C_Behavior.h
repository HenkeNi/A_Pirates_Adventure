#pragma once
#include "../../Component.h"

class SteeringBehavior;

// Rename BoidBehavior or SteeringBehavior??
class C_Behavior : public Component
{
public:
	C_Behavior(GameObject* anOwner = nullptr);

	void		Init(rapidjson::Value& aValue)				override;
	void		HandleMessage(const CompMessage& aMsg)		override;
	void		Update(float aDeltaTime)					override;
	void		LateUpdate(float aDeltaTime)				override;
	void		OnActivate()								override;
	
	C_Behavior* Copy()								  const override;

	void		SetBehavior(SteeringBehavior* aBehavior);

private:
	SteeringBehavior*	m_activeBehavior; // Change to map or priority tree, or something...
	class C_Movement*	m_movement;
};

