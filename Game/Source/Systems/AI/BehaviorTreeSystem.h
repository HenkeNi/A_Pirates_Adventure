#pragma once
#include "Base/System.h"


class BehaviorTreeSystem : public System
{
public:
	BehaviorTreeSystem();
	~BehaviorTreeSystem();
	
	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:

};

