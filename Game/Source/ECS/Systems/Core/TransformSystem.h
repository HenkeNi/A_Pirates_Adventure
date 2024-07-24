#pragma once
#include "../Base/System.h"

class TransformSystem : public System
{
public:
	TransformSystem();
	~TransformSystem();

	void Update(float deltaTime) override;
};