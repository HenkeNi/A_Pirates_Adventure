#pragma once


class Condition
{
public:
	virtual ~Condition() = default;

	virtual void Init()											= 0;
	virtual bool IsConditionSatisfied(float elapsedTime) const	= 0;
};