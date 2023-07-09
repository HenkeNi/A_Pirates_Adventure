#pragma once
#include "BehaviorTreeNode.h"

#include <functional>  // remove later...
// Maybe add an ActionNode base class??



// Action nodes are divided into checks and tasks?!


// Renmame Tasks or Actions?

// Todo, put in Engine??


class MoveToTarget : public BehaviorTreeNode
{
public:
	MoveToTarget(Entity* aTarget = nullptr);

	eBTNodeStatus	Execute(Entity* anEntity) override;
	void			Clear()						 override;

	void			SetCallback(const std::function<void()>& aCallback);
	void			SetTarget(Entity* aTarget);

private:

	// callback? or use derived classes??
	std::function<void()>	m_callback;
	Entity*				m_target;
};



class AttackTarget : public BehaviorTreeNode
{
public:
	AttackTarget(Entity* aTarget = nullptr);

	eBTNodeStatus	Execute(Entity* anEntity) override;
	void			Clear()						 override;

	void			SetTarget(Entity* aTarget);
private:
	Entity*		m_target;
};



class Idle : public BehaviorTreeNode
{
public:
	Idle();

	eBTNodeStatus	Execute(Entity* anEntity) override;
	void			Clear()						 override;

};