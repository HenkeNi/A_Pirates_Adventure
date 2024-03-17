#pragma once
#include "../Base/Condition.h"

	
class ElapsedTimeCondition : public Condition
{
public:
	ElapsedTimeCondition(float duration);

	void Init()									override;
	bool IsSatisfied(float elapsedTime) const	override;

private:
	float m_start;
	float m_duration; // store in component of some sort?? Timer Component...?
};