#pragma once
#include "../../Base/System.h"


class MeleeCombatSystem : public System
{
public:
	MeleeCombatSystem();
	~MeleeCombatSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:

};