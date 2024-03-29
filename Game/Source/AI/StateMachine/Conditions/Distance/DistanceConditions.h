#pragma once
#include "../Base/Condition.h"

// In range of what??
class InRangeCondition : public Condition
{
public:
	InRangeCondition(float range);

	void Init() override;
	bool IsSatisfied(Entity* entity) const override;

private:
	float m_range;
};



// At location? condition







// Put elsewhere?
class HasAttackedCondition : public Condition
{
public:
	void Init() override;
	bool IsSatisfied(Entity* entity) const override;


};