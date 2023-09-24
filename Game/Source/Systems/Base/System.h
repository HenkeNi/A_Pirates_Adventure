#pragma once
#include "../PostMaster/Subscriber.h"

class EntityManager;

class System : public Subscriber
{
public:
	System(unsigned aPriority = 0);
	virtual ~System() = default;

	void Init(EntityManager* anEntityManager);

	virtual void Update(float aDeltaTime)		{};
	virtual	void LateUpdate(float aDeltaTime)	{};
	virtual void Draw()							{};

protected:
	EntityManager*	 m_entityManager;
	unsigned		 m_priority;
};
