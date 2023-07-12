#pragma once
#include "../Base/System.h"

class Entity;

class CombatSystem : public System
{
public:
	CombatSystem();
	~CombatSystem();

	void Receive(Message& aMsg)											override;
	void Update(float aDeltaTime)										override;

private:
	unsigned GetDamageOutput(Entity* anEntity)							   const;
	bool	 ApplyDamageOutput(Entity* anEntity, unsigned aDamage);

	std::vector<Entity*> m_deadEntities;
};