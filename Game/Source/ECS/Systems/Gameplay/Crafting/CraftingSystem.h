#pragma once
#include "../../Base/System.h"


class CraftingSystem : public System
{
public:
	CraftingSystem();
	~CraftingSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

private:
};