#pragma once
#include "PostMaster/Subscriber.h"

class EntityManager;

class System
{
public:
	System(unsigned priority = 0);
	virtual ~System() = default;

	void Init(EntityManager* entityManager);

	virtual void Update(float deltaTime)		{};
	virtual	void LateUpdate(float deltaTime)	{};
	virtual void Draw()							{};

protected:
	EntityManager*	 m_entityManager; // Todo; store reference to ECS instead? have GetSystem function in system manager?
	unsigned		 m_priority;
};
