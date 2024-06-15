#pragma once
#include "PostMaster/Subscriber.h"

class EntityManager;

class System : public Subscriber
{
public:
	System(unsigned priority = 0);
	virtual ~System() = default;

	void Init(EntityManager* entityManager);

	virtual void Update(float deltaTime)		{};
	virtual	void LateUpdate(float deltaTime)	{};
	virtual void Draw()							{};

protected:
	EntityManager*	 m_entityManager;
	unsigned		 m_priority;
};
