#pragma once
#include "../Base/System.h"

class ShakeSystem : public System
{
public:
	ShakeSystem();
	~ShakeSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime) override;
};