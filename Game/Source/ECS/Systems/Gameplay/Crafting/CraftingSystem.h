#pragma once
#include "../../Base/System.h"


class CraftingSystem : public System
{
public:
	CraftingSystem();
	~CraftingSystem();

	void Update(float deltaTime) override;
};