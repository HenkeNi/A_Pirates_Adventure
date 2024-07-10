#pragma once
#include "../../Base/System.h"

// Attack System?
class MeleeCombatSystem : public System
{
public:
	MeleeCombatSystem();
	~MeleeCombatSystem();

	void Update(float deltaTime)	override;

private:

};