#pragma once
#include "../Base/Condition.h"

	
class ElapsedTimeCondition : public Condition
{
public:
	ElapsedTimeCondition(float duration);

	void Init()									override;
	bool IsSatisfied(Entity* entity) const	override;

	void Reset() override;

private:
	//float m_start;

	double m_timestamp;
	float m_duration; // store in component of some sort?? Timer Component...?
};