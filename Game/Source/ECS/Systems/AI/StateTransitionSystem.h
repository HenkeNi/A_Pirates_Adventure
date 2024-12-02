#pragma once
#include "../Base/System.h"

class StateTransitionSystem : public System
{
public:
	StateTransitionSystem();
	~StateTransitionSystem();

	void Update(float deltaTime)	override;

private:
	// bool IsSuspicious(const Entity* entity) const;

	bool ShouldTransitionToIdle(Entity entity) const;
	bool ShouldTransitionToAlert(Entity entity) const;
	bool ShouldTransitionToPatrol(Entity entity) const;
	bool ShouldTransitionToChase(Entity entity) const;
	bool ShouldTransitionToFlee(Entity entity) const;
	bool ShouldTransitionToAttack(Entity entity) const;
};