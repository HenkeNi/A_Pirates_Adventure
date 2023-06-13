#pragma once
#include "SteeringBehavior.h"


class SeekBehavior
{
public:
	SeekBehavior();



private:
	void RandomizeNewTarget();
	
	bool m_shouldRandomizeTarget;
};