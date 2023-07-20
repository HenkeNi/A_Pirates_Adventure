#pragma once
#include "../Base/System.h"

// ResourceSpawnSystem

// replace with a spawn system => entities have a spawn component (tree => spawn logs)?
class ResourceDropSystem : public System
{
public:
	ResourceDropSystem();
	~ResourceDropSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:

};