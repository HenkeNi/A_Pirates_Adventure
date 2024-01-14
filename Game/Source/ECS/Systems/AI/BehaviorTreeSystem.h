#pragma once
#include "../Base/System.h"


class BehaviorTreeSystem : public System
{
public:
	BehaviorTreeSystem();
	~BehaviorTreeSystem();
	
	// Init function for setting up AI??

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:
	void ClearBehaviorTreeNodes();
};