#pragma once
#include "../../Base/System.h"

class Entity;

class CombatSystem : public System
{
public:
	CombatSystem();
	~CombatSystem();

	void		Receive(Message& aMsg)								 override;
	void		Update(float aDeltaTime)							 override;

private:
	void		PerformAttack(Entity* anEntity);
	bool		IsTargetable(Entity* anEntity)							const;

	unsigned				GetDamageOutput(Entity* anEntity)						const;
	// std::vector<Entity*>	GetNearbyEntities()							const;
	bool					ApplyDamageOutput(Entity* anEntity, unsigned aDamage);
};