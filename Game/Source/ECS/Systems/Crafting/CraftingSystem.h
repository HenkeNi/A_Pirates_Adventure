#pragma once
#include "../Base/System.h"


class CraftingSystem : public System
{
public:
	CraftingSystem();
	~CraftingSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:
};