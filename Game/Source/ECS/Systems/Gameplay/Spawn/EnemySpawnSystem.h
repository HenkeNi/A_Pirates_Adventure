#pragma once
#include "../../Base/System.h"


class EnemySpawnSystem : public System
{
public:
	EnemySpawnSystem();
	~EnemySpawnSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;


private:
	void SpawnEnemy(const std::string& type, const CU::Vector2<float>& position);
	bool ShouldSpawn() const;

};