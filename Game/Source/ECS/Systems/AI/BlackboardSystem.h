#pragma once
#include "../Base/System.h"

class BlackboardSystem : public System
{
public:
	BlackboardSystem();
	~BlackboardSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
};