#pragma once
#include "../../Base/System.h"


class EnemySpawnSystem : public System
{
public:
	EnemySpawnSystem();
	~EnemySpawnSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;


private:
	void SpawnEnemy(const std::string& aType, const CU::Vector2<float>& aPosition);
	bool ShouldSpawn() const;

};