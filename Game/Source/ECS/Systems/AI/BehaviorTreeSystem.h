#pragma once
#include "../Base/System.h"


// Merge into a single AISysem?
class BehaviorTreeSystem : public System
{
public:
	BehaviorTreeSystem();
	~BehaviorTreeSystem();
	
	// Init function for setting up AI??

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

private:
	void ClearBehaviorTreeNodes();
};