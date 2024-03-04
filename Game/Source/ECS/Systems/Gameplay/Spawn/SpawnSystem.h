#pragma once
#include "../../Base/System.h"

// Works for enemies, chest, trees, etc??

// or separate ENemySpawnSystem, form LootDropSystem, and ResourceDropSystem?

class SpawnSystem : public System
{
public:
	SpawnSystem();
	~SpawnSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:
	void Spawn(Entity* aSpawner);
};