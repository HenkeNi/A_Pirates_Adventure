#pragma once
#include "../../Base/System.h"


class RangedCombatSystem : public System
{
public:
	RangedCombatSystem();
	~RangedCombatSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:

};