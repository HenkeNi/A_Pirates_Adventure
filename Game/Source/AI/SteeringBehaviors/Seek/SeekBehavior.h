#pragma once
#include "../Base/SteeringBehavior.h"


class SeekBehavior
{
public:
	SeekBehavior();



private:
	void RandomizeNewTarget();
	
	bool m_shouldRandomizeTarget;
};