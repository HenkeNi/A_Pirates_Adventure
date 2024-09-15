#pragma once
#include "../../Base/System.h"


class TransformationSystem : public System
{
public:
	TransformationSystem();
	~TransformationSystem();

	// does calc world position?=

	void Update(float deltaTime) override;
	void SetSignature() override;

private:
	// update children transformations... (positio, rotation, etc)
};