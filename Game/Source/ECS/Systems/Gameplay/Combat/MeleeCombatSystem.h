#pragma once
#include "../../Base/System.h"

// Attack System?
class MeleeCombatSystem : public System
{
public:
	MeleeCombatSystem();
	~MeleeCombatSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

private:

};