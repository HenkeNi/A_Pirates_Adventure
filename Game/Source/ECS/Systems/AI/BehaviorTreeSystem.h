#pragma once
#include "../Base/System.h"


// Merge into a single AISysem?
class BehaviorTreeSystem : public System
{
public:
	BehaviorTreeSystem();
	~BehaviorTreeSystem();
	
	// Init function for setting up AI??
	void Update(float deltaTime)	override;
	void SetSignature() override;

private:
	void ClearBehaviorTreeNodes();
};