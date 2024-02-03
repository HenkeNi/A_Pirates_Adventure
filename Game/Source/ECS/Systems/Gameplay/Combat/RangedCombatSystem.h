#pragma once
#include "../../Base/System.h"

// Rename ProjectileSystem?
class RangedCombatSystem : public System
{
public:
	RangedCombatSystem();
	~RangedCombatSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;
};