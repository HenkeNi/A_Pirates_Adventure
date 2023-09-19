#pragma once
#include "Base/System.h"


class HealthBarSystem : public System
{
public:
	HealthBarSystem();
	~HealthBarSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:

};