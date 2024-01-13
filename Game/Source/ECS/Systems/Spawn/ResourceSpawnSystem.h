#pragma once
#include "../Base/System.h"


// replace with a spawn system => entities have a spawn component (tree => spawn logs)?
class ResourceSpawnSystem : public System
{
public:
	ResourceSpawnSystem();
	~ResourceSpawnSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:

};