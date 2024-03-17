#pragma once
#include "../../Base/System.h"

// Rename ProjectileSystem?
class RangedCombatSystem : public System
{
public:
	RangedCombatSystem();
	~RangedCombatSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
};