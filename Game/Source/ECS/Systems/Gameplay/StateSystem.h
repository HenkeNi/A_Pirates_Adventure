#pragma once
#include "../Base/System.h"

class StateSystem : public System
{
public:
	void Update(float deltaTime) override;
	void SetSignature() override;
};

// TODO; update StateComponent (idle, walking , etc...