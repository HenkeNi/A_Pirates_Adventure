#pragma once
#include "../Base/System.h"


class CombatSystem : public System
{
public:
	CombatSystem();
	~CombatSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:

};