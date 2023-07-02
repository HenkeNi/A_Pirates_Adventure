#pragma once
#include "BehaviorTreeNode.h"

#include <functional>  // remove later...
// Maybe add an ActionNode base class??



// Action nodes are divided into checks and tasks?!


// Renmame Tasks or Actions?

// Todo, put in Engine??

class GameObject;

class MoveToTarget : public BehaviorTreeNode
{
public:
	MoveToTarget(GameObject* aTarget = nullptr);

	eBTNodeStatus	Execute(GameObject* anOwner) override;
	void			Clear()						 override;

	void			SetCallback(const std::function<void()>& aCallback);
	void			SetTarget(GameObject* aTarget);

private:

	// callback? or use derived classes??
	std::function<void()>	m_callback;
	GameObject*				m_target;
};



class AttackTarget : public BehaviorTreeNode
{
public:
	AttackTarget(GameObject* aTarget = nullptr);

	eBTNodeStatus	Execute(GameObject* anOwner) override;
	void			Clear()						 override;

	void			SetTarget(GameObject* aTarget);
private:
	GameObject*		m_target;
};



class Idle : public BehaviorTreeNode
{
public:
	Idle();

	eBTNodeStatus	Execute(GameObject* anOwner) override;
	void			Clear()						 override;

};