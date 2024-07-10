#pragma once
#include "../../Base/System.h"

class Entity;

class CombatSystem : public System, public Subscriber
{
public:
	CombatSystem();
	~CombatSystem();

	void		Receive(Message& message)						 override;
	void		Update(float deltaTime)							 override;

	static std::vector<Entity*> GetAdversaries(const Entity* entity); // GetHostileEntities

private:
	void		PerformAttack(Entity* entity);
	bool		IsTargetable(Entity* entity)						const;

	unsigned	GetDamageOutput(Entity* entity)						const;
	// std::vector<Entity*>	GetNearbyEntities()							const;
	bool		ApplyDamageOutput(Entity* entity, unsigned damage);
	void		ApplyKnockback(Entity* source, Entity* target);
};