#pragma once

class Entity;

class Condition
{
public:
	virtual ~Condition() = default;

	virtual void Init()								= 0;
	virtual bool IsSatisfied(Entity* entity) const	= 0;

	virtual void Reset() {};
};