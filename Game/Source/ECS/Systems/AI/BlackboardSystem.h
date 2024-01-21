#pragma once
#include "../Base/System.h"

class BlackboardSystem : public System
{
public:
	BlackboardSystem();
	~BlackboardSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;
};