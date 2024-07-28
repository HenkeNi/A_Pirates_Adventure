#pragma once
#include "../../Base/System.h"

// Works for enemies, chest, trees, etc??

// or separate ENemySpawnSystem, form LootDropSystem, and ResourceDropSystem?

class SpawnSystem : public System, public Subscriber
{
public:
	SpawnSystem();
	~SpawnSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
	void SetSignature() override;

private:
	void Spawn(Entity spawner);
};