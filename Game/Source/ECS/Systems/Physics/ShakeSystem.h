#pragma once
#include "../Base/System.h"

// Integrate into combat system? together with knockbacks?
class ShakeSystem : public System
{
public:
	ShakeSystem();
	~ShakeSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime) override;
};