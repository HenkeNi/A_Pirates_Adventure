#pragma once
#include "Base/System.h"


class StateMachineSystem : public System
{
public:
	StateMachineSystem();
	~StateMachineSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:

};