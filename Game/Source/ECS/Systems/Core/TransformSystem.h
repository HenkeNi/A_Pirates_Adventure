#pragma once
#include "../Base/System.h"


class TransformSystem : public System
{
public:
	TransformSystem();
	~TransformSystem();

	// does calc world position?=

	void Update(float deltaTime) override;
	void SetSignature() override;

private:
	// update children transformations... (positio, rotation, etc)
	void UpdateSubEntities();
	void UpdateOrientation();
};