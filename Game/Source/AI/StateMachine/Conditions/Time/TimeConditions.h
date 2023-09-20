#pragma once
#include "../Base/Condition.h"

	
class ElapsedTimeCondition : public Condition
{
public:
	ElapsedTimeCondition(float aDuration);

	void Init()											override;
	bool IsConditionSatisfied(float elapsedTime) const	override;

private:
	float m_start;
	float m_duration;
};