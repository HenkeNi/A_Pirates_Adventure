#pragma once
#include "../Base/System.h"

class Entity;

class MapDecorationSystem : public System
{
public:
	MapDecorationSystem();
	~MapDecorationSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:
	void PopulateWithFoilage(const Entity* aMapChunk);
};