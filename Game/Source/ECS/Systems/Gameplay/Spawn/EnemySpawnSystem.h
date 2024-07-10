#pragma once
#include "../../Base/System.h"


class EnemySpawnSystem : public System
{
public:
	EnemySpawnSystem();
	~EnemySpawnSystem();

	void Update(float deltaTime)	override;

private:
	void SpawnEnemy(const std::string& type, const FVector2& position);
	bool ShouldSpawn() const;

};