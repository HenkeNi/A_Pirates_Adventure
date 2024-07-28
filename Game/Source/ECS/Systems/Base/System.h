#pragma once
#include "ECSTypes.h"

class ECS;

class System
{
public:
	System(unsigned priority = 0);
	virtual ~System() = default;

	void Init(ECS* ecs);
	virtual void SetSignature() = 0;

	virtual void Update(float deltaTime)		{};
	virtual	void LateUpdate(float deltaTime)	{};
	virtual void Draw()							{};

protected:
	ECS*		m_ecs;
	Signatures	m_signatures;
	unsigned	m_priority;
};